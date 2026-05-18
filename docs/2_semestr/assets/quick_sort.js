/** Quick Sort — partition + рекурсія (sort_viz.css, sort_viz.js) */

const QUICK_SOURCE = [
  { n: 104, html: '<span class="ty">int</span> <span class="fn">partition</span>(<span class="ty">std::vector</span>&lt;<span class="ty">int</span>&gt;&amp; arr, <span class="ty">int</span> low, <span class="ty">int</span> high) {' },
  { n: 105, html: '    <span class="ty">int</span> pivot = arr[high];' },
  { n: 106, html: '    <span class="ty">int</span> i = low - <span class="op">1</span>;' },
  { n: 108, html: '    <span class="kw">for</span> (<span class="ty">int</span> j = low; j &lt; high; j++) {' },
  { n: 109, html: '        <span class="kw">if</span> (arr[j] &lt;= pivot) {' },
  { n: 110, html: '            i++;' },
  { n: 111, html: '            std::swap(arr[i], arr[j]);' },
  { n: 115, html: '    std::swap(arr[i + <span class="op">1</span>], arr[high]);' },
  { n: 116, html: '    <span class="kw">return</span> i + <span class="op">1</span>;' },
  { n: 119, html: '<span class="kw">void</span> <span class="fn">quickSort</span>(<span class="ty">std::vector</span>&lt;<span class="ty">int</span>&gt;&amp; arr, <span class="ty">int</span> low, <span class="ty">int</span> high) {' },
  { n: 120, html: '    <span class="kw">if</span> (low &lt; high) {' },
  { n: 121, html: '        <span class="ty">int</span> pi = partition(arr, low, high);' },
  { n: 124, html: '        quickSort(arr, low, pi - <span class="op">1</span>);' },
  { n: 125, html: '        quickSort(arr, pi + <span class="op">1</span>, high);' },
];

const QUICK_CODE_COMMENTS = {
  105: '// pivot — останній елемент діапазону [low … high]',
  109: '// елементи ≤ pivot зсуваємо ліворуч',
};

function quickStepComment(step) {
  if (step.type === 'pivot' || step.type === 'compare' || step.type === 'advanceI') {
    return QUICK_CODE_COMMENTS[105] + '  ' + QUICK_CODE_COMMENTS[109];
  }
  if (step.type === 'pivotSwap') {
    return 'Pivot на фінальній позиції pi: ліворуч ≤ pivot, праворуч > pivot.';
  }
  if (step.type === 'recurseLeft' || step.type === 'recurseRight') {
    return 'Рекурсивно сортуємо підмасив, де ще можуть бути невпорядковані елементи.';
  }
  return '';
}

function quickRenderVars(step) {
  const fmt = (v) =>
    v === null || v === undefined
      ? '<span class="val null">—</span>'
      : '<span class="val">' + v + '</span>';
  const fields = [
    ['low', step.low],
    ['high', step.high],
    ['i', step.i],
    ['j', step.j],
    ['pivot', step.pivot],
    ['pi', step.pi],
  ];
  return fields.map(([name, value]) =>
    '<span class="var"><span class="name">' + name +
    '</span><span class="eq">=</span>' + fmt(value) + '</span>'
  ).join('');
}

function quickCellClass(idx, step) {
  if (step.sortedIndices && step.sortedIndices.has(idx)) {
    return 'sorted';
  }
  return '';
}

function rangeIndices(lo, hi) {
  const idx = [];
  for (let k = lo; k <= hi; k++) idx.push(k);
  return idx;
}

function generateQuickSteps(initial) {
  const a = initial.slice();
  const n = a.length;
  const sortedIndices = new Set();
  const list = [];

  function pushStep(step) {
    list.push({
      ...step,
      sortedIndices: new Set(sortedIndices),
      cellClass: quickCellClass,
    });
  }

  function pushPartitionSteps(low, high) {
    const pivot = a[high];
    const pivotIdx = high;

    pushStep({
      type: 'pivot',
      arr: a.slice(),
      n,
      low,
      high,
      i: low - 1,
      j: null,
      pivot,
      pi: null,
      pivotIdx,
      activeLines: [105, 106],
      affectedLines: [108],
      highlightIndices: [high],
      caption:
        'partition(arr, ' + low + ', ' + high + '): pivot = arr[' + high + '] = ' + pivot + ', i = ' + (low - 1) + '.',
    });

    let i = low - 1;
    for (let j = low; j < high; j++) {
      const fits = a[j] <= pivot;
      pushStep({
        type: 'compare',
        arr: a.slice(),
        n,
        low,
        high,
        i,
        j,
        pivot,
        pi: null,
        pivotIdx,
        activeLines: [108, 109],
        affectedLines: [110],
        highlightIndices: [j, high],
        caption:
          'j = ' + j + ': arr[' + j + '] (' + a[j] + ') <= pivot (' + pivot + ')? → ' + (fits ? 'так' : 'ні') + '.',
      });
      if (fits) {
        i++;
        if (i !== j) {
          const ghostI = a[i];
          const ghostJ = a[j];
          [a[i], a[j]] = [a[j], a[i]];
          pushStep({
            type: 'swap',
            arr: a.slice(),
            n,
            low,
            high,
            i,
            j,
            pivot,
            pi: null,
            pivotIdx,
            activeLines: [110, 111],
            affectedLines: [109],
            highlightIndices: [i, j],
            ghosts: [{ at: i, val: ghostI }, { at: j, val: ghostJ }],
            caption: 'i++ → ' + i + '; std::swap(arr[' + i + '], arr[' + j + ']).',
          });
        } else {
          pushStep({
            type: 'advanceI',
            arr: a.slice(),
            n,
            low,
            high,
            i,
            j,
            pivot,
            pi: null,
            pivotIdx,
            activeLines: [110],
            highlightIndices: [j],
            caption: 'i++ → ' + i + '; j == i, обмін не потрібен.',
          });
        }
      }
    }

    const pi = i + 1;
    sortedIndices.add(pi);

    if (pi !== high) {
      const ghostPi = a[pi];
      const ghostHigh = a[high];
      [a[pi], a[high]] = [a[high], a[pi]];
      pushStep({
        type: 'pivotSwap',
        arr: a.slice(),
        n,
        low,
        high,
        i,
        j: null,
        pivot,
        pi,
        pivotIdx: pi,
        activeLines: [115],
        affectedLines: [116],
        highlightIndices: [pi, high],
        ghosts: [{ at: pi, val: ghostPi }, { at: high, val: ghostHigh }],
        caption: 'std::swap(arr[' + pi + '], arr[' + high + ']): pivot = ' + a[pi] + ' на позиції pi = ' + pi + '.',
      });
    } else {
      pushStep({
        type: 'pivotSwap',
        arr: a.slice(),
        n,
        low,
        high,
        i,
        j: null,
        pivot,
        pi,
        pivotIdx: pi,
        activeLines: [115],
        highlightIndices: [pi],
        caption: 'pi = ' + pi + ': pivot уже на місці, фінальний обмін не потрібен.',
      });
    }

    pushStep({
      type: 'partitionEnd',
      arr: a.slice(),
      n,
      low,
      high,
      i,
      j: null,
      pivot,
      pi,
      pivotIdx: pi,
      activeLines: [116],
      highlightIndices: [pi],
      caption:
        'return pi = ' + pi + '; елементи [' + low + '…' + (pi - 1) + '] ≤ pivot, [' + (pi + 1) + '…' + high + '] > pivot.',
    });

    return pi;
  }

  function markSingleton(low, high) {
    if (low !== high || low < 0 || low >= n) return;
    if (sortedIndices.has(low)) return;
    sortedIndices.add(low);
    pushStep({
      type: 'baseCase',
      arr: a.slice(),
      n,
      low,
      high,
      i: null,
      j: null,
      pivot: a[low],
      pi: low,
      activeLines: [120],
      affectedLines: [119],
      highlightIndices: [low],
      caption:
        'quickSort(arr, ' + low + ', ' + high + '): один елемент — вже на місці, індекс ' + low + ' зафіксовано.',
    });
  }

  function quickSort(low, high) {
    if (low > high) return;

    if (low === high) {
      markSingleton(low, high);
      return;
    }

    pushStep({
      type: 'recurse',
      arr: a.slice(),
      n,
      low,
      high,
      i: null,
      j: null,
      pivot: null,
      pi: null,
      activeLines: [120, 121],
      highlightIndices: rangeIndices(low, high),
      caption: 'quickSort(arr, ' + low + ', ' + high + '): сортуємо підмасив індексів [' + low + ' … ' + high + '].',
    });

    const pi = pushPartitionSteps(low, high);

    const leftHigh = pi - 1;
    const rightLow = pi + 1;

    if (low <= leftHigh) {
      if (low === leftHigh) {
        markSingleton(low, leftHigh);
      } else {
        pushStep({
          type: 'recurseLeft',
          arr: a.slice(),
          n,
          low,
          high: leftHigh,
          i: null,
          j: null,
          pivot: null,
          pi,
          activeLines: [124],
          affectedLines: [120],
          highlightIndices: rangeIndices(low, leftHigh),
          caption: 'Ліва частина: quickSort(arr, ' + low + ', ' + leftHigh + ').',
        });
        quickSort(low, leftHigh);
      }
    }

    if (rightLow <= high) {
      if (rightLow === high) {
        markSingleton(rightLow, high);
      } else {
        pushStep({
          type: 'recurseRight',
          arr: a.slice(),
          n,
          low: rightLow,
          high,
          i: null,
          j: null,
          pivot: null,
          pi,
          activeLines: [125],
          affectedLines: [120],
          highlightIndices: rangeIndices(rightLow, high),
          caption: 'Права частина: quickSort(arr, ' + rightLow + ', ' + high + ').',
        });
        quickSort(rightLow, high);
      }
    }
  }

  pushStep({
    type: 'init',
    arr: a.slice(),
    n,
    low: 0,
    high: n - 1,
    i: null,
    j: null,
    pivot: null,
    pi: null,
    activeLines: [119, 120],
    highlightIndices: [],
    caption:
      n > 0
        ? 'quickSort(arr, 0, ' + (n - 1) + '): сортуємо весь масив рекурсивно через partition.'
        : 'Порожній масив — сортування не потрібне.',
  });

  if (n === 1) {
    markSingleton(0, 0);
  } else if (n > 1) {
    quickSort(0, n - 1);
  }

  for (let k = 0; k < n; k++) sortedIndices.add(k);
  pushStep({
    type: 'done',
    arr: a.slice(),
    n,
    low: 0,
    high: n - 1,
    i: null,
    j: null,
    pivot: null,
    pi: null,
    activeLines: [125],
    highlightIndices: [],
    caption: 'Масив відсортовано.',
  });

  return list;
}

SortViz.init({
  title: 'Quick Sort',
  source: QUICK_SOURCE,
  generateSteps: generateQuickSteps,
  getComment: quickStepComment,
  renderVars: quickRenderVars,
});
