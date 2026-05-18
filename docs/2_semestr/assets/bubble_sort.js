/** Bubble Sort — логіка кроків (стилі: sort_viz.css, рушій: sort_viz.js) */

const BUBBLE_SOURCE = [
  { n: 35, html: '<span class="kw">void</span> <span class="fn">bubbleSort</span>(<span class="ty">std::vector</span>&lt;<span class="ty">int</span>&gt;&amp; arr) {' },
  { n: 36, html: '    <span class="ty">int</span> n = arr.size();' },
  { n: 39, html: '    <span class="kw">for</span> (<span class="ty">int</span> i = <span class="op">0</span>; i &lt; n - <span class="op">1</span>; i++) {' },
  { n: 41, html: '        <span class="kw">for</span> (<span class="ty">int</span> j = <span class="op">0</span>; j &lt; n - i - <span class="op">1</span>; j++) {' },
  { n: 42, html: '            <span class="kw">if</span> (arr[j] &gt; arr[j + <span class="op">1</span>]) {' },
  { n: 43, html: '                std::swap(arr[j], arr[j + <span class="op">1</span>]);' },
  { n: 44, html: '            }' },
  { n: 45, html: '        }' },
  { n: 46, html: '    }' },
  { n: 47, html: '}' },
];

const BUBBLE_CODE_COMMENTS = {
  38: '// N проходів',
  40: '// Кожного разу зменшуємо область пошуку',
  43: '// «Бульбашка» спливає вправо',
};

function bubbleStepComment(step) {
  if (step.type === 'outer') {
    return `${BUBBLE_CODE_COMMENTS[38]}  ${BUBBLE_CODE_COMMENTS[40]}`;
  }
  if (step.type === 'swap') return BUBBLE_CODE_COMMENTS[43];
  if (step.type === 'compare') return BUBBLE_CODE_COMMENTS[40];
  return '';
}

function generateBubbleSteps(initial) {
  const a = initial.slice();
  const n = a.length;
  const list = [];

  list.push({
    type: 'init',
    arr: a.slice(),
    n,
    i: null,
    j: null,
    activeLines: [36],
    affectedLines: [],
    highlightIndices: [],
    sortedFrom: n,
    caption: 'Ініціалізація: n = arr.size(), масив заповнено випадковими значеннями.',
  });

  for (let i = 0; i < n - 1; i++) {
    list.push({
      type: 'outer',
      arr: a.slice(),
      n,
      i,
      j: null,
      activeLines: [39],
      affectedLines: [40],
      highlightIndices: [],
      sortedFrom: n - i,
      caption: `Зовнішній прохід: i = ${i}. Порівнюємо елементи з індексами 0 … ${n - i - 2}.`,
    });

    for (let j = 0; j < n - i - 1; j++) {
      const needSwap = a[j] > a[j + 1];

      list.push({
        type: 'compare',
        arr: a.slice(),
        n,
        i,
        j,
        activeLines: [41, 42],
        affectedLines: [],
        highlightIndices: [j, j + 1],
        sortedFrom: n - i,
        caption: `Порівняння: arr[${j}] (${a[j]}) > arr[${j + 1}] (${a[j + 1]})? → ${needSwap ? 'так, міняємо місцями' : 'ні, залишаємо'}.`,
      });

          if (needSwap) {
            const ghostLeft = a[j];
            const ghostRight = a[j + 1];
            [a[j], a[j + 1]] = [a[j + 1], a[j]];
            list.push({
              type: 'swap',
              arr: a.slice(),
              n,
              i,
              j,
              activeLines: [43],
              affectedLines: [42],
              highlightIndices: [j, j + 1],
              sortedFrom: n - i,
              ghosts: [
                { at: j, val: ghostLeft },
                { at: j + 1, val: ghostRight },
              ],
              caption: `std::swap(arr[${j}], arr[${j + 1}]). Найбільший елемент «спливає» праворуч.`,
            });
          }
    }
  }

  list.push({
    type: 'done',
    arr: a.slice(),
    n,
    i: n - 1,
    j: null,
    activeLines: [47],
    affectedLines: [],
    highlightIndices: [],
    sortedFrom: 0,
    caption: 'Сортування завершено. Усі елементи впорядковані.',
  });

  return list;
}

SortViz.init({
  title: 'Bubble Sort',
  source: BUBBLE_SOURCE,
  generateSteps: generateBubbleSteps,
  getComment: bubbleStepComment,
});
