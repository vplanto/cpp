/**
 * Спільний рушій для покрокових візуалізацій сортування.
 * Кожен алгоритм: окремий HTML + JS з викликом SortViz.init({ ... }).
 */
const SortViz = (() => {
  const CD = '</div>';

  function randomArray(size, min = 5, range = 88) {
    return Array.from({ length: size }, () => Math.floor(Math.random() * range) + min);
  }

  const BAR_WRAP_MIN_H = 200;

  function getBarWrapHeight(arrayEl) {
    const wraps = arrayEl.querySelectorAll('.bar-wrap');
    let maxH = 0;

    wraps.forEach((wrap) => {
      const h = wrap.getBoundingClientRect().height;
      if (h > maxH) maxH = h;
    });

    if (maxH < 1) {
      const slot = arrayEl.closest('.array-viz-slot');
      if (slot) {
        const style = getComputedStyle(slot);
        const padY = parseFloat(style.paddingTop) + parseFloat(style.paddingBottom);
        maxH = slot.clientHeight - padY;
      }
    }

    return Math.max(Math.round(maxH), BAR_WRAP_MIN_H);
  }

  function barHeightPx(val, maxVal, wrapPx) {
    const inner = Math.max(wrapPx - 4, 1);
    return Math.max(8, Math.round((val / maxVal) * inner));
  }

  function buildCellHtml(cls, idx, val) {
    return [
      '<div class="', cls, '" data-idx="', idx, '" data-val="', val, '">',
      '<span class="idx">[', idx, ']</span>',
      '<div class="bar-wrap">',
      '<div class="bar-ghost" aria-hidden="true">', CD,
      '<div class="bar">', CD,
      CD,
      '<span class="val">', val, '</span>',
      CD,
    ].join('');
  }

  function cellClass(step, idx, compareSet) {
    const sorted = step.sortedFrom !== undefined && idx >= step.sortedFrom;
    const compare = compareSet.has(idx);
    const extra = step.cellClass ? step.cellClass(idx, step) : '';

    return [
      'cell',
      sorted ? 'sorted' : '',
      compare && step.type === 'swap' ? 'swap' : '',
      compare && step.type === 'compare' ? 'compare' : '',
      compare && step.type === 'pivot' ? 'pivot' : '',
      extra,
    ].filter(Boolean).join(' ');
  }

  function applyCellState(cell, step, idx, maxVal, compareSet, barWrapH) {
    const val = step.arr[idx];
    cell.className = cellClass(step, idx, compareSet);
    cell.dataset.val = String(val);
    cell.querySelector('.val').textContent = val;

    const bar = cell.querySelector('.bar');
    const ghost = cell.querySelector('.bar-ghost');
    const ghostEntry = (step.ghosts || []).find((g) => g.at === idx);
    const wrapH = barWrapH || BAR_WRAP_MIN_H;

    bar.style.height = barHeightPx(val, maxVal, wrapH) + 'px';

    if (ghostEntry) {
      ghost.style.height = barHeightPx(ghostEntry.val, maxVal, wrapH) + 'px';
      ghost.classList.add('is-visible');
    } else {
      ghost.style.height = '0';
      ghost.classList.remove('is-visible');
    }
  }

  function renderCode(codeEl, source, step) {
    const active = new Set(step.activeLines || []);
    const affected = new Set(step.affectedLines || []);

    codeEl.innerHTML = source.map(({ n, html }) => {
      const cls = [
        'code-line',
        active.has(n) ? 'active' : '',
        affected.has(n) && !active.has(n) ? 'affected' : '',
        active.has(n) && affected.has(n) ? 'active affected' : '',
      ].filter(Boolean).join(' ');

      return [
        '<div class="', cls, '" data-line="', n, '">',
        '<span class="ln">', n, '</span>',
        '<span class="src">', html, '</span>',
        CD,
      ].join('');
    }).join('');
  }

  function renderArray(arrayEl, step) {
    const maxVal = Math.max(...step.arr, 1);
    const compareSet = new Set(step.highlightIndices || []);
    const cells = arrayEl.querySelectorAll('.cell');

    if (cells.length !== step.arr.length) {
      arrayEl.innerHTML = step.arr.map((val, idx) => {
        const cls = cellClass(step, idx, compareSet);
        return buildCellHtml(cls, idx, val);
      }).join('');
    }

    function applyAll() {
      const barWrapH = getBarWrapHeight(arrayEl);
      arrayEl.querySelectorAll('.cell').forEach((cell, idx) => {
        applyCellState(cell, step, idx, maxVal, compareSet, barWrapH);
      });
    }

    applyAll();
    requestAnimationFrame(applyAll);
  }

  function formatVar(v) {
    return v === null || v === undefined
      ? '<span class="val null">—</span>'
      : '<span class="val">' + v + '</span>';
  }

  function defaultRenderVars(step) {
    const fields = step.vars || [
      ['n', step.n],
      ['i', step.i],
      ['j', step.j],
      ['розмір', step.arr.length],
    ];

    return fields.map(([name, value]) =>
      '<span class="var"><span class="name">' + name +
      '</span><span class="eq">=</span>' + formatVar(value) + '</span>'
    ).join('');
  }

  function renderFooter(els, step, getComment, renderVars) {
    els.captionEl.textContent = step.caption || '';

    const comment = getComment ? getComment(step) : (step.codeComment || '');
    els.codeCommentEl.textContent = comment;
    els.codeCommentEl.classList.toggle('empty', !comment);

    const render = renderVars || defaultRenderVars;
    els.varsEl.innerHTML = render(step);
  }

  function init(config) {
    const {
      title,
      subtitle = 'покроковий перегляд (лекція 21)',
      source,
      generateSteps,
      getComment = () => '',
      renderVars,
      arraySize = 9,
    } = config;

    const titleEl = document.getElementById('viz-title');
    if (titleEl) titleEl.textContent = title;

    const headerEl = document.querySelector('header');
    if (headerEl && !titleEl) {
      headerEl.innerHTML = '<strong>' + title + '</strong> — ' + subtitle;
    }

    const codeEl = document.getElementById('code');
    const arrayEl = document.getElementById('array');
    const captionEl = document.getElementById('caption');
    const varsEl = document.getElementById('vars');
    const codeCommentEl = document.getElementById('codeComment');
    const stepInfoEl = document.getElementById('stepInfo');
    const btnPrev = document.getElementById('btnPrev');
    const btnNext = document.getElementById('btnNext');
    const btnReset = document.getElementById('btnReset');

    const footerEls = { captionEl, codeCommentEl, varsEl };

    let steps = [];
    let stepIndex = 0;

    function render() {
      const step = steps[stepIndex];
      renderCode(codeEl, source, step);
      renderArray(arrayEl, step);
      renderFooter(footerEls, step, getComment, renderVars);
      stepInfoEl.textContent = (stepIndex + 1) + ' / ' + steps.length;
      btnPrev.disabled = stepIndex === 0;
      btnNext.disabled = stepIndex >= steps.length - 1;
    }

    function reset() {
      steps = generateSteps(randomArray(arraySize));
      stepIndex = 0;
      render();
    }

    btnNext.addEventListener('click', () => {
      if (stepIndex < steps.length - 1) {
        stepIndex++;
        render();
      }
    });

    btnPrev.addEventListener('click', () => {
      if (stepIndex > 0) {
        stepIndex--;
        render();
      }
    });

    btnReset.addEventListener('click', reset);

    document.addEventListener('keydown', (e) => {
      if (e.key === 'ArrowRight' && !btnNext.disabled) btnNext.click();
      if (e.key === 'ArrowLeft' && !btnPrev.disabled) btnPrev.click();
    });

    let resizeTimer;
    window.addEventListener('resize', () => {
      clearTimeout(resizeTimer);
      resizeTimer = setTimeout(() => {
        if (steps.length) renderArray(arrayEl, steps[stepIndex]);
      }, 80);
    });

    reset();
  }

  return {
    init,
    randomArray,
    renderCode,
    renderArray,
    renderFooter,
    getBarWrapHeight,
    barHeightPx,
  };
})();
