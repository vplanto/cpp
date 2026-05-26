/**
 * Спільний рушій для покрокових візуалізацій обходу графів та пошуку компонент.
 * Кожен алгоритм: окремий HTML + JS з викликом GraphViz.init({ ... }).
 */
const GraphViz = (() => {
  const CD = '</div>';

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

  function renderVisitedArray(visitedEl, visited, labelMap) {
    visitedEl.innerHTML = visited.map((val, idx) => {
      const label = labelMap ? (labelMap[idx] !== undefined ? labelMap[idx] : idx) : idx;
      let displayVal = val;
      let isTrue = val === true;
      if (typeof val === 'number') {
        if (val === Infinity || val >= 999999) {
          displayVal = '∞';
          isTrue = false;
        } else {
          displayVal = val;
          isTrue = true;
        }
      }
      const cls = isTrue ? 'visited-cell is-true' : 'visited-cell';
      return `<div class="${cls}">
        <span class="v-idx">[${label}]</span>
        <span class="v-val">${displayVal}</span>
      </div>`;
    }).join('');
  }

  function renderQueue(queueEl, q, labelMap) {
    if (!q || q.length === 0) {
      queueEl.innerHTML = '<span class="queue-empty">порожня</span>';
      return;
    }
    queueEl.innerHTML = q.map((item, idx) => {
      let text;
      if (typeof item === 'object' && item !== null) {
        const label = labelMap ? (labelMap[item.u] !== undefined ? labelMap[item.u] : item.u) : item.u;
        text = `(${item.d}, ${label})`;
      } else {
        text = labelMap ? (labelMap[item] !== undefined ? labelMap[item] : item) : item;
      }
      const itemHtml = `<span class="queue-item">${text}</span>`;
      if (idx === q.length - 1) return itemHtml;
      return itemHtml + '<span class="queue-arrow">←</span>';
    }).join('');
  }

  function defaultRenderVars(step, labelMap) {
    const fields = [
      ['n', step.n],
      ['v', step.v],
      ['components', step.components],
      ['cur', step.cur],
      ['nb', step.nb],
      ['u', step.u],
      ['d', step.d],
      ['newDist', step.newDist],
    ].filter(([name, val]) => {
      if (val === undefined) return false;
      if (name === 'components' && step.components === undefined) return false;
      return true;
    });

    return fields.map(([name, value]) => {
      const isNull = value === null || value === undefined;
      let formattedValue = isNull ? '—' : value;
      if (!isNull && labelMap && (name === 'v' || name === 'cur' || name === 'nb' || name === 'u')) {
        formattedValue = labelMap[value] !== undefined ? labelMap[value] : value;
      }
      if (formattedValue === Infinity || formattedValue >= 999999) {
        formattedValue = '∞';
      }
      const valClass = isNull ? 'val null' : 'val';
      return `<span class="var"><span class="name">${name}</span><span class="eq">=</span><span class="${valClass}">${formattedValue}</span></span>`;
    }).join('');
  }

  function renderFooter(els, step, getComment, renderVars, labelMap) {
    els.captionEl.textContent = step.caption || '';

    const comment = getComment ? getComment(step) : (step.codeComment || '');
    els.codeCommentEl.textContent = comment;
    els.codeCommentEl.classList.toggle('empty', !comment);

    const render = renderVars || ((s) => defaultRenderVars(s, labelMap));
    els.varsEl.innerHTML = render(step);
  }

  function renderGraph(svgEl, graph, step) {
    const nodesMap = step.nodeStates || {};
    const edgesMap = step.edgeStates || {};

    svgEl.querySelectorAll('.graph-node').forEach(nodeEl => {
      const id = parseInt(nodeEl.dataset.id);
      const state = nodesMap[id] || 'unvisited';
      
      nodeEl.classList.remove('queued', 'current', 'visited');
      if (state !== 'unvisited') {
        nodeEl.classList.add(state);
      }
    });

    svgEl.querySelectorAll('.graph-edge').forEach(edgeEl => {
      const id = edgeEl.dataset.id;
      const revId = id.split('-').reverse().join('-');
      const state = edgesMap[id] || edgesMap[revId] || 'inactive';
      
      edgeEl.classList.remove('active', 'visited');
      if (state !== 'inactive') {
        edgeEl.classList.add(state);
      }
    });
  }

  function init(config) {
    const {
      title,
      subtitle = 'покроковий обхід (лекція 22)',
      source,
      graph,
      generateSteps,
      getComment = () => '',
      renderVars,
    } = config;

    const titleEl = document.getElementById('viz-title');
    if (titleEl) titleEl.textContent = title;

    const headerEl = document.querySelector('header');
    if (headerEl && !titleEl) {
      headerEl.innerHTML = '<strong>' + title + '</strong> — ' + subtitle;
    }

    const codeEl = document.getElementById('code');
    const svgEl = document.getElementById('graph-svg');
    const visitedEl = document.getElementById('visited-array');
    const queueEl = document.getElementById('queue-viz');
    const captionEl = document.getElementById('caption');
    const varsEl = document.getElementById('vars');
    const codeCommentEl = document.getElementById('codeComment');
    const stepInfoEl = document.getElementById('stepInfo');
    const btnPrev = document.getElementById('btnPrev');
    const btnNext = document.getElementById('btnNext');
    const btnReset = document.getElementById('btnReset');

    const footerEls = { captionEl, codeCommentEl, varsEl };

    // Build label map from graph nodes
    const labelMap = {};
    graph.nodes.forEach(n => {
      labelMap[n.id] = n.label;
    });

    svgEl.innerHTML = '';
    
    // Малюємо ребра
    graph.edges.forEach(edge => {
      const uNode = graph.nodes.find(n => n.id === edge.u);
      const vNode = graph.nodes.find(n => n.id === edge.v);
      if (uNode && vNode) {
        const line = document.createElementNS('http://www.w3.org/2000/svg', 'line');
        line.setAttribute('x1', uNode.x);
        line.setAttribute('y1', uNode.y);
        line.setAttribute('x2', vNode.x);
        line.setAttribute('y2', vNode.y);
        line.setAttribute('class', 'graph-edge');
        line.setAttribute('data-id', `${edge.u}-${edge.v}`);
        svgEl.appendChild(line);

        // Якщо ребро має вагу, малюємо напис ваги по центру
        if (edge.w !== undefined) {
          const text = document.createElementNS('http://www.w3.org/2000/svg', 'text');
          const midX = (uNode.x + vNode.x) / 2;
          const midY = (uNode.y + vNode.y) / 2;
          text.setAttribute('x', midX);
          text.setAttribute('y', midY);
          text.setAttribute('class', 'edge-weight');
          text.textContent = edge.w;
          svgEl.appendChild(text);
        }
      }
    });

    // Малюємо вершини
    graph.nodes.forEach(node => {
      const g = document.createElementNS('http://www.w3.org/2000/svg', 'g');
      g.setAttribute('class', 'graph-node');
      g.setAttribute('data-id', node.id);

      const circle = document.createElementNS('http://www.w3.org/2000/svg', 'circle');
      circle.setAttribute('cx', node.x);
      circle.setAttribute('cy', node.y);
      circle.setAttribute('r', 18);

      const text = document.createElementNS('http://www.w3.org/2000/svg', 'text');
      text.setAttribute('x', node.x);
      text.setAttribute('y', node.y);
      text.textContent = node.label;

      g.appendChild(circle);
      g.appendChild(text);
      svgEl.appendChild(g);
    });

    let steps = [];
    let stepIndex = 0;

    function render() {
      const step = steps[stepIndex];
      renderCode(codeEl, source, step);
      renderGraph(svgEl, graph, step);
      renderVisitedArray(visitedEl, step.visited, labelMap);
      renderQueue(queueEl, step.q, labelMap);
      renderFooter(footerEls, step, getComment, renderVars, labelMap);

      stepInfoEl.textContent = (stepIndex + 1) + ' / ' + steps.length;
      btnPrev.disabled = stepIndex === 0;
      btnNext.disabled = stepIndex >= steps.length - 1;
    }

    function reset() {
      steps = generateSteps(graph);
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

    reset();
  }

  return {
    init,
    renderCode,
    renderVisitedArray,
    renderQueue,
    renderFooter,
    renderGraph,
  };
})();
