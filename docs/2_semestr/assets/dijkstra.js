/** Логіка покрокової візуалізації для Алгоритму Дейкстри */

const DIJKSTRA_SOURCE = [
  { n: 454, html: '<span class="ty">std::vector</span>&lt;<span class="ty">int</span>&gt; <span class="fn">dijkstra</span>(<span class="kw">const</span> Graph&amp; graph, <span class="ty">int</span> start) {' },
  { n: 456, html: '    <span class="ty">std::vector</span>&lt;<span class="ty">int</span>&gt; <span class="fn">dist</span>(graph.size(), <span class="ty">std::numeric_limits</span>&lt;<span class="ty">int</span>&gt;::max());' },
  { n: 457, html: '    dist[start] = <span class="op">0</span>;' },
  { n: 460, html: '    <span class="ty">std::priority_queue</span>&lt;<span class="ty">std::pair</span>&lt;<span class="ty">int</span>,<span class="ty">int</span>&gt;, ...&gt; pq;' },
  { n: 464, html: '    pq.push({<span class="op">0</span>, start});' },
  { n: 466, html: '    <span class="kw">while</span> (!pq.empty()) {' },
  { n: 467, html: '        <span class="kw">auto</span> [d, u] = pq.top(); pq.pop();' },
  { n: 469, html: '        <span class="kw">if</span> (d &gt; dist[u]) <span class="kw">continue</span>;' },
  { n: 471, html: '        <span class="kw">for</span> (<span class="kw">auto</span> [v, w] : graph[u]) {' },
  { n: 472, html: '            <span class="ty">int</span> newDist = dist[u] + w;' },
  { n: 473, html: '            <span class="kw">if</span> (newDist &lt; dist[v]) {' },
  { n: 474, html: '                dist[v] = newDist;' },
  { n: 475, html: '                pq.push({newDist, v});' },
  { n: 476, html: '            }' },
  { n: 477, html: '        }' },
  { n: 478, html: '    }' },
  { n: 479, html: '    <span class="kw">return</span> dist;' },
  { n: 480, html: '}' },
];

const DIJKSTRA_GRAPH = {
  nodes: [
    { id: 0, label: 'A', x: 60, y: 140 },
    { id: 1, label: 'B', x: 200, y: 70 },
    { id: 2, label: 'C', x: 200, y: 210 },
    { id: 3, label: 'E', x: 340, y: 140 },
    { id: 4, label: 'D', x: 460, y: 140 }
  ],
  edges: [
    { u: 0, v: 1, w: 2 },
    { u: 0, v: 2, w: 4 },
    { u: 1, v: 4, w: 5 },
    { u: 1, v: 3, w: 1 },
    { u: 2, v: 3, w: 3 }
  ]
};

const DIJKSTRA_ADJ = {
  0: [ { v: 1, w: 2 }, { v: 2, w: 4 } ],
  1: [ { v: 0, w: 2 }, { v: 4, w: 5 }, { v: 3, w: 1 } ],
  2: [ { v: 0, w: 4 }, { v: 3, w: 3 } ],
  3: [ { v: 1, w: 1 }, { v: 2, w: 3 } ],
  4: [ { v: 1, w: 5 } ]
};

function generateDijkstraSteps(graph) {
  const n = graph.nodes.length;
  const steps = [];

  let dist = Array(n).fill(Infinity);
  let pq = []; // Array of {d, u}
  let u = null;
  let d = null;
  let v = null;
  let w = null;
  let newDist = null;
  let parents = Array(n).fill(null);
  let finalized = Array(n).fill(false);

  function getStates(activeEdge) {
    const nodeStates = {};
    graph.nodes.forEach(node => {
      if (node.id === u) {
        nodeStates[node.id] = 'current';
      } else if (pq.some(item => item.u === node.id)) {
        nodeStates[node.id] = 'queued';
      } else if (finalized[node.id]) {
        nodeStates[node.id] = 'visited';
      } else {
        nodeStates[node.id] = 'unvisited';
      }
    });

    const edgeStates = {};
    graph.edges.forEach(edge => {
      const edgeId = `${edge.u}-${edge.v}`;
      const revId = `${edge.v}-${edge.u}`;
      
      const isTreeEdge = (parents[edge.v] === edge.u || parents[edge.u] === edge.v);

      if (activeEdge && (edgeId === activeEdge || revId === activeEdge)) {
        edgeStates[edgeId] = 'active';
      } else if (isTreeEdge) {
        edgeStates[edgeId] = 'visited';
      } else {
        edgeStates[edgeId] = 'inactive';
      }
    });

    return { nodeStates, edgeStates };
  }

  function addStep(lineNum, caption, activeEdge = null) {
    pq.sort((a, b) => a.d - b.d || a.u - b.u);
    const { nodeStates, edgeStates } = getStates(activeEdge);
    steps.push({
      n,
      u,
      d,
      v,
      newDist,
      q: pq.map(x => ({ d: x.d, u: x.u })),
      visited: [...dist],
      nodeStates,
      edgeStates,
      activeLines: [lineNum],
      caption
    });
  }

  // 456: std::vector<int> dist(...)
  addStep(456, "Ініціалізація: створюємо масив відстаней dist, заповнений нескінченністю (∞).");

  // 457: dist[start] = 0;
  dist[0] = 0;
  addStep(457, "Встановлюємо відстань до стартової вершини A (0) рівною 0: dist[A] = 0.");

  // 460: std::priority_queue<...> pq;
  addStep(460, "Створюємо мін-купу (чергу з пріоритетами) pq для впорядкування вершин за відстанню.");

  // 464: pq.push({0, start});
  pq.push({ d: 0, u: 0 });
  addStep(464, "Додаємо стартову вершину A з пріоритетом 0 до купи: pq.push({0, A}).");

  while (pq.length > 0) {
    // 466: while (!pq.empty())
    addStep(466, `Перевіряємо, чи купа pq порожня. Купа містить елементи, продовжуємо обхід.`);

    // 467: auto [d, u] = pq.top(); pq.pop();
    pq.sort((a, b) => a.d - b.d || a.u - b.u);
    const top = pq.shift();
    d = top.d;
    u = top.u;
    addStep(467, `Дістаємо з купи вершину з найменшою відомою відстанню: u = ${graph.nodes[u].label}, відома відстань d = ${d}.`);

    // 469: if (d > dist[u]) continue;
    if (d > dist[u]) {
      addStep(469, `Оскільки витягнута відстань d (${d}) є більшою за вже знайдену dist[${graph.nodes[u].label}] (${dist[u]}), цей запис застарілий. Ігноруємо його (continue).`);
      u = null;
      d = null;
      continue;
    }
    
    finalized[u] = true;
    addStep(469, `Відстань d (${d}) є оптимальною (d <= dist[${graph.nodes[u].label}]). Фіксуємо найкоротший шлях до вершини ${graph.nodes[u].label}.`);

    const neighbors = DIJKSTRA_ADJ[u] || [];
    for (let i = 0; i < neighbors.length; i++) {
      const edge = neighbors[i];
      v = edge.v;
      w = edge.w;
      const edgeKey = `${u}-${v}`;

      // 471: for (auto [v, w] : graph[u])
      addStep(471, `Розглядаємо сусіда v = ${graph.nodes[v].label} через ребро вагою w = ${w}.`, edgeKey);

      // 472: int newDist = dist[u] + w;
      newDist = dist[u] + w;
      addStep(472, `Обчислюємо альтернативну відстань до ${graph.nodes[v].label} через ${graph.nodes[u].label}: newDist = dist[${graph.nodes[u].label}] + w = ${dist[u]} + ${w} = ${newDist}.`, edgeKey);

      // 473: if (newDist < dist[v])
      if (newDist < dist[v]) {
        addStep(473, `Оскільки альтернативна відстань newDist (${newDist}) є меншою за відому dist[${graph.nodes[v].label}] (${dist[v] === Infinity ? '∞' : dist[v]}), оновлюємо її.`, edgeKey);

        // 474: dist[v] = newDist;
        dist[v] = newDist;
        parents[v] = u;
        addStep(474, `Оновлюємо відстань до ${graph.nodes[v].label}: dist[${graph.nodes[v].label}] = ${newDist}.`, edgeKey);

        // 475: pq.push({newDist, v});
        pq.push({ d: newDist, u: v });
        addStep(475, `Додаємо пару {${newDist}, ${graph.nodes[v].label}} до купи pq для подальшого аналізу.`, edgeKey);
      } else {
        addStep(473, `Альтернативна відстань newDist (${newDist}) не є кращою за поточну dist[${graph.nodes[v].label}] (${dist[v]}). Пропускаємо.`, edgeKey);
      }
      
      v = null;
      w = null;
      newDist = null;
    }

    u = null;
    d = null;
  }

  // 466: loop termination check
  addStep(466, "Купа pq порожня. Обхід Дейкстри завершено.");

  // 479: return dist
  addStep(479, "Повертаємо підрахований масив найкоротших відстаней dist.");

  return steps;
}

GraphViz.init({
  title: "Алгоритм Дейкстри",
  subtitle: "покроковий пошук найкоротшого шляху (лекція 22)",
  source: DIJKSTRA_SOURCE,
  graph: DIJKSTRA_GRAPH,
  generateSteps: generateDijkstraSteps
});
