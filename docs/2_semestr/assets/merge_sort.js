/** Merge Sort — divide, conquer, merge (sort_viz.css, sort_viz.js) */

const MERGE_SOURCE = [
  { n: 175, html: '<span class="kw">void</span> <span class="fn">merge</span>(<span class="ty">std::vector</span>&lt;<span class="ty">int</span>&gt;&amp; arr, <span class="ty">int</span> left, <span class="ty">int</span> mid, <span class="ty">int</span> right) {' },
  { n: 176, html: '    <span class="ty">int</span> n1 = mid - left + <span class="op">1</span>;' },
  { n: 177, html: '    <span class="ty">int</span> n2 = right - mid;' },
  { n: 180, html: '    <span class="ty">std::vector</span>&lt;<span class="ty">int</span>&gt; L(n1), R(n2);' },
  { n: 182, html: '    <span class="kw">for</span> (<span class="ty">int</span> i = <span class="op">0</span>; i &lt; n1; i++) L[i] = arr[left + i];' },
  { n: 183, html: '    <span class="kw">for</span> (<span class="ty">int</span> i = <span class="op">0</span>; i &lt; n2; i++) R[i] = arr[mid + <span class="op">1</span> + i];' },
  { n: 186, html: '    <span class="ty">int</span> i = <span class="op">0</span>, j = <span class="op">0</span>, k = left;' },
  { n: 187, html: '    <span class="kw">while</span> (i &lt; n1 &amp;&amp; j &lt; n2) {' },
  { n: 188, html: '        <span class="kw">if</span> (L[i] &lt;= R[j]) {' },
  { n: 189, html: '            arr[k++] = L[i++];' },
  { n: 191, html: '            arr[k++] = R[j++];' },
  { n: 196, html: '    <span class="kw">while</span> (i &lt; n1) arr[k++] = L[i++];' },
  { n: 197, html: '    <span class="kw">while</span> (j &lt; n2) arr[k++] = R[j++];' },
  { n: 200, html: '<span class="kw">void</span> <span class="fn">mergeSort</span>(<span class="ty">std::vector</span>&lt;<span class="ty">int</span>&gt;&amp; arr, <span class="ty">int</span> left, <span class="ty">int</span> right) {' },
  { n: 201, html: '    <span class="kw">if</span> (left &lt; right) {' },
  { n: 202, html: '        <span class="ty">int</span> mid = left + (right - left) / <span class="op">2</span>;' },
  { n: 204, html: '        mergeSort(arr, left, mid);' },
  { n: 205, html: '        mergeSort(arr, mid + <span class="op">1</span>, right);' },
  { n: 206, html: '        merge(arr, left, mid, right);' },
];

const MERGE_CODE_COMMENTS = {
  179: '// Тимчасові масиви L і R',
  185: '// Злиття двох відсортованих половин',
};

function mergeStepComment(step) {
  if (step.type === 'copyL' || step.type === 'copyR') {
    return MERGE_CODE_COMMENTS[179];
  }
  if (step.type === 'mergeCompare' || step.type === 'mergeWrite' || step.type === 'mergeFlush') {
    return MERGE_CODE_COMMENTS[185];
  }
  if (step.type === 'divide') {
    return 'Divide: ділимо [left … right] навпіл, потім Conquer + Merge.';
  }
  return '';
}

function mergeRenderVars(step) {
  const fmt = (v) =>
    v === null || v === undefined
      ? '<span class="val null">—</span>'
      : '<span class="val">' + v + '</span>';
  const fields = [
    ['left', step.left],
    ['right', step.right],
    ['mid', step.mid],
  ];
  if (step.n1 != null) fields.push(['n1', step.n1]);
  if (step.n2 != null) fields.push(['n2', step.n2]);
  if (step.i != null) fields.push(['i', step.i]);
  if (step.j != null) fields.push(['j', step.j]);
  if (step.k != null) fields.push(['k', step.k]);
  return fields.map(([name, value]) =>
    '<span class="var"><span class="name">' + name +
    '</span><span class="eq">=</span>' + fmt(value) + '</span>'
  ).join('');
}

function mergeCellClass(idx, step) {
  if (step.type === 'done') {
    return 'sorted';
  }
  const ar = step.activeRange;
  const outside = ar && (idx < ar.left || idx > ar.right);
  const locally = step.locallySortedIndices && step.locallySortedIndices.has(idx);
  if (locally) {
    return 'locally-sorted';
  }
  if (outside) {
    return 'not-in-range';
  }
  return '';
}

function rangeIndices(lo, hi) {
  const idx = [];
  for (let k = lo; k <= hi; k++) idx.push(k);
  return idx;
}

function activeRangeOf(left, right) {
  return { left, right };
}

function generateMergeSteps(initial) {
  const a = initial.slice();
  const n = a.length;
  const locallySortedIndices = new Set();
  const list = [];

  function pushStep(step) {
    const ar = step.activeRange;
    list.push({
      ...step,
      activeRange: ar ? { left: ar.left, right: ar.right } : null,
      locallySortedIndices: new Set(locallySortedIndices),
      cellClass: mergeCellClass,
    });
  }

  function markLocallySorted(left, right) {
    for (let x = left; x <= right; x++) locallySortedIndices.add(x);
  }

  function pushMergeSteps(left, mid, right) {
    const n1 = mid - left + 1;
    const n2 = right - mid;
    const L = a.slice(left, mid + 1);
    const R = a.slice(mid + 1, right + 1);
    const range = activeRangeOf(left, right);

    pushStep({
      type: 'mergeStart',
      arr: a.slice(),
      n,
      left,
      right,
      mid,
      n1,
      n2,
      i: null,
      j: null,
      k: null,
      activeRange: range,
      activeLines: [175, 176, 177],
      affectedLines: [180],
      highlightIndices: rangeIndices(left, right),
      caption:
        'merge(arr, ' + left + ', ' + mid + ', ' + right + '): n1 = ' + n1 + ', n2 = ' + n2 + '.',
    });

    pushStep({
      type: 'copyL',
      arr: a.slice(),
      n,
      left,
      right,
      mid,
      n1,
      n2,
      i: null,
      j: null,
      k: null,
      activeRange: range,
      activeLines: [180, 182],
      highlightIndices: rangeIndices(left, mid),
      caption: 'Копіюємо ліву половину arr[' + left + '…' + mid + '] у тимчасовий масив L.',
    });

    pushStep({
      type: 'copyR',
      arr: a.slice(),
      n,
      left,
      right,
      mid,
      n1,
      n2,
      i: null,
      j: null,
      k: null,
      activeRange: range,
      activeLines: [183],
      highlightIndices: rangeIndices(mid + 1, right),
      caption: 'Копіюємо праву половину arr[' + (mid + 1) + '…' + right + '] у тимчасовий масив R.',
    });

    pushStep({
      type: 'mergeLoop',
      arr: a.slice(),
      n,
      left,
      right,
      mid,
      n1,
      n2,
      i: 0,
      j: 0,
      k: left,
      activeRange: range,
      activeLines: [186, 187],
      highlightIndices: rangeIndices(left, right),
      caption: 'i = 0, j = 0, k = left = ' + left + ' — починаємо злиття.',
    });

    let i = 0;
    let j = 0;
    let k = left;

    while (i < n1 && j < n2) {
      const srcL = left + i;
      const srcR = mid + 1 + j;
      const takeLeft = L[i] <= R[j];
      pushStep({
        type: 'mergeCompare',
        arr: a.slice(),
        n,
        left,
        right,
        mid,
        n1,
        n2,
        i,
        j,
        k,
        srcL,
        srcR,
        activeRange: range,
        activeLines: [187, 188],
        highlightIndices: [srcL, srcR],
        caption:
          'L[' + i + '] (з arr[' + srcL + '] = ' + L[i] + ') <= R[' + j + '] (з arr[' + srcR + '] = ' + R[j] + ')? → ' +
          (takeLeft ? 'так' : 'ні') + '.',
      });

      const writeK = k;
      const oldVal = a[writeK];
      const val = takeLeft ? L[i++] : R[j++];
      a[writeK] = val;
      pushStep({
        type: 'mergeWrite',
        arr: a.slice(),
        n,
        left,
        right,
        mid,
        n1,
        n2,
        i,
        j,
        k: writeK,
        activeRange: range,
        activeLines: takeLeft ? [189] : [191],
        affectedLines: [188],
        highlightIndices: [writeK],
        ghosts: [{ at: writeK, val: oldVal }],
        caption:
          (takeLeft ? 'arr[' + writeK + '] = L[' + (i - 1) + '] = ' : 'arr[' + writeK + '] = R[' + (j - 1) + '] = ') +
          val + ' (було ' + oldVal + '), k++.',
      });
      k++;
    }

    while (i < n1) {
      const writeK = k;
      const oldVal = a[writeK];
      const val = L[i];
      a[writeK] = val;
      pushStep({
        type: 'mergeFlush',
        arr: a.slice(),
        n,
        left,
        right,
        mid,
        n1,
        n2,
        i,
        j,
        k: writeK,
        activeRange: range,
        activeLines: [196],
        highlightIndices: [writeK],
        ghosts: [{ at: writeK, val: oldVal }],
        caption: 'Залишок L: arr[' + writeK + '] = L[' + i + '] = ' + val + ' (було ' + oldVal + ').',
      });
      i++;
      k++;
    }

    while (j < n2) {
      const writeK = k;
      const oldVal = a[writeK];
      const val = R[j];
      a[writeK] = val;
      pushStep({
        type: 'mergeFlush',
        arr: a.slice(),
        n,
        left,
        right,
        mid,
        n1,
        n2,
        i,
        j,
        k: writeK,
        activeRange: range,
        activeLines: [197],
        highlightIndices: [writeK],
        ghosts: [{ at: writeK, val: oldVal }],
        caption: 'Залишок R: arr[' + writeK + '] = R[' + j + '] = ' + val + ' (було ' + oldVal + ').',
      });
      j++;
      k++;
    }

    markLocallySorted(left, right);
    pushStep({
      type: 'mergeEnd',
      arr: a.slice(),
      n,
      left,
      right,
      mid,
      n1,
      n2,
      i,
      j,
      k,
      activeRange: range,
      activeLines: [197],
      highlightIndices: rangeIndices(left, right),
      caption: 'Злиття завершено: arr[' + left + '…' + right + '] локально відсортовано.',
    });
  }

  function markSingleton(left, right) {
    if (left !== right) return;
    markLocallySorted(left, right);
    pushStep({
      type: 'baseCase',
      arr: a.slice(),
      n,
      left,
      right,
      mid: left,
      n1: null,
      n2: null,
      i: null,
      j: null,
      k: null,
      activeRange: activeRangeOf(left, right),
      activeLines: [201],
      affectedLines: [200],
      highlightIndices: [left],
      caption: 'mergeSort: один елемент arr[' + left + '] — вже відсортований.',
    });
  }

  function mergeSort(left, right) {
    if (left > right) return;

    if (left === right) {
      markSingleton(left, right);
      return;
    }

    const mid = left + Math.floor((right - left) / 2);

    pushStep({
      type: 'divide',
      arr: a.slice(),
      n,
      left,
      right,
      mid,
      n1: null,
      n2: null,
      i: null,
      j: null,
      k: null,
      activeRange: activeRangeOf(left, right),
      activeLines: [201, 202],
      affectedLines: [204, 205, 206],
      highlightIndices: rangeIndices(left, right),
      caption:
        'mergeSort(arr, ' + left + ', ' + right + '): mid = ' + mid + ' → [' + left + '…' + mid + '] | [' + (mid + 1) + '…' + right + '].',
    });

    pushStep({
      type: 'recurseLeft',
      arr: a.slice(),
      n,
      left,
      right: mid,
      mid,
      n1: null,
      n2: null,
      i: null,
      j: null,
      k: null,
      activeRange: activeRangeOf(left, mid),
      activeLines: [204],
      highlightIndices: rangeIndices(left, mid),
      caption: 'Ліва половина: mergeSort(arr, ' + left + ', ' + mid + ').',
    });
    mergeSort(left, mid);

    pushStep({
      type: 'recurseRight',
      arr: a.slice(),
      n,
      left: mid + 1,
      right,
      mid,
      n1: null,
      n2: null,
      i: null,
      j: null,
      k: null,
      activeRange: activeRangeOf(mid + 1, right),
      activeLines: [205],
      highlightIndices: rangeIndices(mid + 1, right),
      caption: 'Права половина: mergeSort(arr, ' + (mid + 1) + ', ' + right + ').',
    });
    mergeSort(mid + 1, right);

    pushStep({
      type: 'mergeCall',
      arr: a.slice(),
      n,
      left,
      right,
      mid,
      n1: null,
      n2: null,
      i: null,
      j: null,
      k: null,
      activeRange: activeRangeOf(left, right),
      activeLines: [206],
      highlightIndices: rangeIndices(left, right),
      caption: 'Обидві половини готові → merge(arr, ' + left + ', ' + mid + ', ' + right + ').',
    });
    pushMergeSteps(left, mid, right);
  }

  pushStep({
    type: 'init',
    arr: a.slice(),
    n,
    left: 0,
    right: n > 0 ? n - 1 : null,
    mid: null,
    n1: null,
    n2: null,
    i: null,
    j: null,
    k: null,
    activeRange: n > 0 ? activeRangeOf(0, n - 1) : null,
    activeLines: [200, 201],
    highlightIndices: [],
    caption:
      n > 0
        ? 'mergeSort(arr, 0, ' + (n - 1) + '): divide → conquer → merge.'
        : 'Порожній масив.',
  });

  if (n === 1) {
    markSingleton(0, 0);
  } else if (n > 1) {
    mergeSort(0, n - 1);
  }

  pushStep({
    type: 'done',
    arr: a.slice(),
    n,
    left: 0,
    right: n - 1,
    mid: null,
    n1: null,
    n2: null,
    i: null,
    j: null,
    k: null,
    activeRange: null,
    activeLines: [206],
    highlightIndices: [],
    caption: 'Масив відсортовано.',
  });

  return list;
}

SortViz.init({
  title: 'Merge Sort',
  source: MERGE_SOURCE,
  generateSteps: generateMergeSteps,
  getComment: mergeStepComment,
  renderVars: mergeRenderVars,
});
