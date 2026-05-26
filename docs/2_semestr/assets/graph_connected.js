/** Логіка покрокової візуалізації для Зв'язаного Графа */

const GRAPH_SOURCE = [
  { n: 379, html: '<span class="ty">int</span> <span class="fn">countComponents</span>(<span class="ty">int</span> n, <span class="kw">const</span> <span class="ty">std::vector</span>&lt;<span class="ty">std::vector</span>&lt;<span class="ty">int</span>&gt;&gt;&amp; graph) {' },
  { n: 380, html: '    <span class="ty">std::vector</span>&lt;<span class="kw">bool</span>&gt; <span class="fn">visited</span>(n, <span class="kw">false</span>);' },
  { n: 381, html: '    <span class="ty">int</span> components = <span class="op">0</span>;' },
  { n: 383, html: '    <span class="kw">for</span> (<span class="ty">int</span> v = <span class="op">0</span>; v &lt; n; v++) {' },
  { n: 384, html: '        <span class="kw">if</span> (visited[v]) <span class="kw">continue</span>;' },
  { n: 386, html: '        components++;' },
  { n: 388, html: '        <span class="ty">std::queue</span>&lt;<span class="ty">int</span>&gt; q;' },
  { n: 389, html: '        q.push(v);' },
  { n: 390, html: '        visited[v] = <span class="kw">true</span>;' },
  { n: 391, html: '        <span class="kw">while</span> (!q.empty()) {' },
  { n: 392, html: '            <span class="ty">int</span> cur = q.front(); q.pop();' },
  { n: 393, html: '            <span class="kw">for</span> (<span class="ty">int</span> nb : graph[cur]) {' },
  { n: 394, html: '                <span class="kw">if</span> (!visited[nb]) {' },
  { n: 395, html: '                    visited[nb] = <span class="kw">true</span>;' },
  { n: 396, html: '                    q.push(nb);' },
  { n: 397, html: '                }' },
  { n: 398, html: '            }' },
  { n: 399, html: '        }' },
  { n: 400, html: '    }' },
  { n: 401, html: '    <span class="kw">return</span> components;' },
  { n: 402, html: '}' },
];

const CONNECTED_GRAPH = {
  nodes: [
    { id: 0, label: '0', x: 80, y: 70 },
    { id: 1, label: '1', x: 200, y: 70 },
    { id: 2, label: '2', x: 80, y: 190 },
    { id: 3, label: '3', x: 320, y: 70 },
    { id: 4, label: '4', x: 440, y: 70 },
    { id: 5, label: '5', x: 320, y: 190 }
  ],
  edges: [
    { u: 0, v: 1 },
    { u: 0, v: 2 },
    { u: 1, v: 2 },
    { u: 1, v: 3 },
    { u: 3, v: 4 },
    { u: 3, v: 5 },
    { u: 4, v: 5 }
  ]
};

const CONNECTED_ADJ = {
  0: [1, 2],
  1: [0, 2, 3],
  2: [0, 1],
  3: [1, 4, 5],
  4: [3, 5],
  5: [3, 4]
};

function generateConnectedSteps(graph) {
  const n = graph.nodes.length;
  const steps = [];
  
  let visited = Array(n).fill(false);
  let componentsCount = 0;
  let q = [];
  let cur = null;
  let nb = null;
  let vLoop = null;
  let treeEdges = new Set();

  function getStates(activeEdge) {
    const nodeStates = {};
    graph.nodes.forEach(node => {
      if (node.id === cur) {
        nodeStates[node.id] = 'current';
      } else if (q.includes(node.id)) {
        nodeStates[node.id] = 'queued';
      } else if (visited[node.id]) {
        nodeStates[node.id] = 'visited';
      } else {
        nodeStates[node.id] = 'unvisited';
      }
    });

    const edgeStates = {};
    graph.edges.forEach(edge => {
      const edgeId = `${edge.u}-${edge.v}`;
      const revId = `${edge.v}-${edge.u}`;
      if (activeEdge && (edgeId === activeEdge || revId === activeEdge)) {
        edgeStates[edgeId] = 'active';
      } else if (treeEdges.has(edgeId) || treeEdges.has(revId)) {
        edgeStates[edgeId] = 'visited';
      } else {
        edgeStates[edgeId] = 'inactive';
      }
    });

    return { nodeStates, edgeStates };
  }

  function addStep(lineNum, caption, activeEdge = null) {
    const { nodeStates, edgeStates } = getStates(activeEdge);
    steps.push({
      n,
      v: vLoop,
      components: componentsCount,
      cur,
      nb,
      q: [...q],
      visited: [...visited],
      nodeStates,
      edgeStates,
      activeLines: [lineNum],
      caption
    });
  }

  // 380: std::vector<bool> visited(n, false)
  addStep(380, "Ініціалізація: створюємо масив visited розміром n = 6, заповнений false.");

  // 381: int components = 0
  addStep(381, "Ініціалізація: починаємо з components = 0.");

  for (let v = 0; v < n; v++) {
    vLoop = v;
    // 383: for (int v = 0; v < n; v++)
    addStep(383, `Зовнішній цикл: перевіряємо вершину v = ${v}.`);

    // 384: if (visited[v]) continue
    if (visited[v]) {
      addStep(384, `visited[${v}] є true. Вершина вже відвідана у попередньому BFS, тому пропускаємо її (continue).`);
      continue;
    }
    addStep(384, `visited[${v}] є false. Вершина ще не відвідана, запускаємо новий обхід.`);

    // 386: components++
    componentsCount++;
    addStep(386, `Знайдено нову компоненту зв'язності! Збільшуємо components до ${componentsCount}.`);

    // 388: std::queue<int> q
    q = [];
    addStep(388, "Створюємо порожню чергу q для обходу в ширину (BFS).");

    // 389: q.push(v)
    q.push(v);
    addStep(389, `Додаємо початкову вершину компоненти v = ${v} до черги q.`);

    // 390: visited[v] = true
    visited[v] = true;
    addStep(390, `Позначаємо вершину ${v} як відвідану: visited[${v}] = true.`);

    while (q.length > 0) {
      // 391: while (!q.empty())
      addStep(391, `Черга q не порожня (q = [${q.join(', ')}]). Продовжуємо обхід.`);

      // 392: int cur = q.front(); q.pop()
      cur = q.shift();
      addStep(392, `Вилучаємо вершину cur = ${cur} з голови черги для обробки.`);

      const neighbors = CONNECTED_ADJ[cur] || [];
      for (let i = 0; i < neighbors.length; i++) {
        nb = neighbors[i];
        const edgeKey = `${cur}-${nb}`;

        // 393: for (int nb : graph[cur])
        addStep(393, `Розглядаємо сусіда nb = ${nb} для вершини cur = ${cur}.`, edgeKey);

        // 394: if (!visited[nb])
        if (!visited[nb]) {
          addStep(394, `visited[${nb}] є false. Вершина ${nb} ще не була відвідана.`, edgeKey);

          // 395: visited[nb] = true
          visited[nb] = true;
          addStep(395, `Позначаємо сусідню вершину як відвідану: visited[${nb}] = true.`, edgeKey);

          // 396: q.push(nb)
          q.push(nb);
          treeEdges.add(edgeKey);
          addStep(396, `Додаємо вершину ${nb} в кінець черги q для подальшого обходу.`, edgeKey);
        } else {
          addStep(394, `visited[${nb}] є true. Вершина ${nb} вже була відвідана раніше, ігноруємо її.`, edgeKey);
        }
        nb = null;
      }
      cur = null;
    }
    // 391: loop termination check
    addStep(391, "Черга q порожня. BFS обхід поточної компоненти завершено.");
  }

  vLoop = null;
  // 401: return components
  addStep(401, `Зовнішній цикл завершив перевірку всіх вершин від 0 до 5. Повертаємо підраховану кількість компонент: components = ${componentsCount}.`);

  return steps;
}

GraphViz.init({
  title: "Компоненти зв'язності (Зв'язаний граф)",
  subtitle: "покроковий BFS обхід (лекція 22)",
  source: GRAPH_SOURCE,
  graph: CONNECTED_GRAPH,
  generateSteps: generateConnectedSteps
});
