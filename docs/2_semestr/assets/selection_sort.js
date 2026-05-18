/** Selection Sort — логіка кроків (sort_viz.css, sort_viz.js) */

const SELECTION_SOURCE = [
  { n: 59, html: '<span class="kw">void</span> <span class="fn">selectionSort</span>(<span class="ty">std::vector</span>&lt;<span class="ty">int</span>&gt;&amp; arr) {' },
  { n: 60, html: '    <span class="ty">int</span> n = arr.size();' },
  { n: 62, html: '    <span class="kw">for</span> (<span class="ty">int</span> i = <span class="op">0</span>; i &lt; n - <span class="op">1</span>; i++) {' },
  { n: 63, html: '        <span class="ty">int</span> minIdx = i;' },
  { n: 66, html: '        <span class="kw">for</span> (<span class="ty">int</span> j = i + <span class="op">1</span>; j &lt; n; j++) {' },
  { n: 67, html: '            <span class="kw">if</span> (arr[j] &lt; arr[minIdx]) {' },
  { n: 68, html: '                minIdx = j;' },
  { n: 69, html: '            }' },
  { n: 70, html: '        }' },
  { n: 72, html: '        std::swap(arr[i], arr[minIdx]);' },
  { n: 74, html: '}' },
];

const SELECTION_CODE_COMMENTS = {
  65: '// Шукаємо мінімум в невідсортованій частині',
};

function selectionStepComment(step) {
  if (step.type === 'outer' || step.type === 'compare' || step.type === 'updateMin') {
    return SELECTION_CODE_COMMENTS[65];
  }
  if (step.type === 'swap') {
    return 'Мінімум з невідсортованої частини ставимо на позицію i.';
  }
  return '';
}

function selectionRenderVars(step) {
  const fields = [
    ['n', step.n],
    ['i', step.i],
    ['j', step.j],
    ['minIdx', step.minIdx],
    ['розмір', step.arr.length],
  ];
  return fields.map(([name, value]) =>
    '<span class="var"><span class="name">' + name +
    '</span><span class="eq">=</span>' +
    (value === null || value === undefined
      ? '<span class="val null">—</span>'
      : '<span class="val">' + value + '</span>') +
    '</span>'
  ).join('');
}

function generateSelectionSteps(initial) {
  const a = initial.slice();
  const n = a.length;
  const list = [];

  list.push({
    type: 'init',
    arr: a.slice(),
    n,
    i: null,
    j: null,
    minIdx: null,
    activeLines: [60],
    affectedLines: [],
    highlightIndices: [],
    sortedBefore: 0,
    caption: 'Ініціалізація: n = arr.size(), масив заповнено випадковими значеннями.',
  });

  for (let i = 0; i < n - 1; i++) {
    let minIdx = i;

    list.push({
      type: 'outer',
      arr: a.slice(),
      n,
      i,
      j: null,
      minIdx,
      activeLines: [62, 63],
      affectedLines: [66],
      highlightIndices: [i],
      sortedBefore: i,
      caption: 'Зовнішній цикл: i = ' + i + ', minIdx = i. Шукаємо мінімум у діапазоні [' + (i + 1) + ' … ' + (n - 1) + '].',
    });

    for (let j = i + 1; j < n; j++) {
      const isNewMin = a[j] < a[minIdx];
      list.push({
        type: 'compare',
        arr: a.slice(),
        n,
        i,
        j,
        minIdx,
        activeLines: [66, 67],
        affectedLines: [65],
        highlightIndices: [j, minIdx],
        sortedBefore: i,
        caption: 'Порівняння: arr[' + j + '] (' + a[j] + ') < arr[' + minIdx + '] (' + a[minIdx] + ')? → ' + (isNewMin ? 'так' : 'ні') + '.',
      });
      if (isNewMin) {
        minIdx = j;
        list.push({
          type: 'updateMin',
          arr: a.slice(),
          n,
          i,
          j,
          minIdx,
          activeLines: [68],
          affectedLines: [67],
          highlightIndices: [j],
          sortedBefore: i,
          caption: 'Новий мінімум: minIdx = ' + j + ' (значення ' + a[j] + ').',
        });
      }
    }

    if (minIdx !== i) {
      const ghostAtI = a[i];
      const ghostAtMin = a[minIdx];
      [a[i], a[minIdx]] = [a[minIdx], a[i]];
      list.push({
        type: 'swap',
        arr: a.slice(),
        n,
        i,
        j: null,
        minIdx,
        activeLines: [72],
        affectedLines: [62, 63],
        highlightIndices: [i, minIdx],
        sortedBefore: i + 1,
        ghosts: [{ at: i, val: ghostAtI }, { at: minIdx, val: ghostAtMin }],
        caption: 'std::swap(arr[' + i + '], arr[' + minIdx + ']). Позиція ' + i + ' зафіксована.',
      });
    } else {
      list.push({
        type: 'noSwap',
        arr: a.slice(),
        n,
        i,
        j: null,
        minIdx,
        activeLines: [72],
        highlightIndices: [i],
        sortedBefore: i + 1,
        caption: 'minIdx == i: обмін не потрібен, arr[' + i + '] = ' + a[i] + ' вже мінімальний у хвості.',
      });
    }
  }

  list.push({
    type: 'done',
    arr: a.slice(),
    n,
    i: n - 1,
    j: null,
    minIdx: null,
    activeLines: [74],
    highlightIndices: [],
    sortedBefore: n,
    caption: 'Сортування завершено.',
  });

  return list;
}

SortViz.init({
  title: 'Selection Sort',
  source: SELECTION_SOURCE,
  generateSteps: generateSelectionSteps,
  getComment: selectionStepComment,
  renderVars: selectionRenderVars,
});
