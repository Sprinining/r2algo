### A*（A-Star）寻路算法

A* 算法是计算机科学中一种极其高效的**启发式路径寻找与图遍历算法**。它于 1968 年被提出，至今仍广泛应用于游戏开发（如 NPC 寻路、RTS 游戏点击移动）、地图导航（GPS 路线规划）以及机器人路径规划中。

A* 算法的核心优势在于：**既能像 Dijkstra 算法那样保证找到一条最短路径，又能像最佳优先搜索（BFS）那样利用几何辅助信息快速收敛，大大提高搜索效率。**

#### 一、 核心公式：它是如何抉择的？

A* 算法在决定下一步走哪一个节点时，会为周围的每一个候选节点计算一个综合代价评估值 $f(n)$：

$$f(n) = g(n) + h(n)$$

* **$g(n)$（实际代价）**：从**起点**到当前节点 $n$ 的**实际已消耗**代价（比如走过的格子数或物理距离）。
* **$h(n)$（启发预估代价）**：从当前节点 $n$ 到**终点**的**预计未消耗**代价。这是 A* 算法拥有“视力”的关键。
* **$f(n)$（总估价）**：从起点通过节点 $n$ 到达终点的**预估总代价**。A* 每次都会优先选择 $f(n)$ 值最小的节点进行拓展。

##### 启发函数 $h(n)$ 的两条铁律
1. **必须因地制宜**：在网格地图中，通常使用**曼哈顿距离**（只能前后左右移动时，坐标差绝对值之和）或**欧几里得距离**（允许任意方向移动时，两点间的直线物理距离）作为 $h(n)$ 的值。
2. **绝对不能“过分悲观”**：$h(n)$ 对剩余距离的预估**必须小于或等于实际的真实距离**（数学上称为可采纳性 Admissibility）。如果估大了，算法会变得草率，可能会漏掉真正的最短路。

#### 二、 算法运行的核心机制

A* 算法在执行时，主要依靠两个列表来管理和维护节点状态：

1. **Open List（开启列表）**：存放所有**已被发现但尚未考察**的节点（待拓展的候选人名单）。通常用**最小堆（优先队列）**实现，以便瞬间踢出 $f(n)$ 最小的节点。
2. **Close List（关闭列表）**：存放所有**已经考察过**的节点。一旦处理完就移入这里，防止重复搜索，避免死循环。

##### 算法执行步骤：
1. 将**起点**放入 `Open List`。
2. **循环执行以下步骤**，直到 `Open List` 为空或找到了终点：
   * 在 `Open List` 中找出 **$f(n)$ 值最小**的节点，将其作为当前立足点，并把它挪入 `Close List`。
   * 判断当前节点是否为**终点**。如果是，说明路径已找到，直接根据节点的父节点指针**回溯**出整条路径，算法结束。
   * 如果不是终点，找出当前节点所有**相邻的有效节点**（忽略障碍物和已在 `Close List` 中的节点）。
   * 对于每个邻居节点：
     * 如果它**不在** `Open List` 中：计算它的 $g, h, f$ 值，将当前节点设为它的**父节点**，然后把它加入 `Open List`。
     * 如果它**已经在** `Open List` 中：检查通过当前节点到达那里的路径是否更近（即新计算出的 $g$ 值是否更小）。如果是，更新它的 $g$ 值和 $f$ 值，并将它的父节点改为当前节点。
3. 如果 `Open List` 变空了还没找到终点，说明起点和终点被障碍物完全隔开，**无路可通**。

---

#### 三、 A* 与 Dijkstra 的本质区别

虽然 A* 与 Dijkstra 在代码结构上高度相似（都包含优先队列和路径松弛操作），但它们的寻路逻辑和效率有着天壤之别。

##### 1. 评分标准的“盲目”与“远见”
* **Dijkstra 算法**：公式为 $\text{Score} = g(n)$。它是一个严谨的“历史主义者”，只看谁现在离起点最近。它完全不抬头看终点在哪个方向。
* **A* 算法**：公式为 $\text{Score} = g(n) + h(n)$。它是一个兼顾历史与未来的“远见主义者”，不仅看走过来累不累，更要看这个点是不是顺着终点的方向。

##### 2. 搜索图形的“水流”与“导弹”
* **Dijkstra（水流泼地）**：在一片开阔的平原上，为了找到正东方向 10 米处的终点，Dijkstra 会 360 度无死角地向四周盲目蔓延。它最终会把以起点为中心、半径 10 米的**一整圈圆形面积内的所有格子全部遍历一遍**，才会碰到终点。
* **A*（导弹追踪）**：同样的场景，A* 算了一下，发现往西、往南走会导致离终点越来越远（$h$ 暴涨，$f$ 飙升）。因此，A* 会**近乎走成一条直线，笔直地戳向东边的终点**，免去了无数南辕北辙的冤枉路。

##### 3. 复杂地形下的“优雅退化”
如果遇到死胡同，A* 这种直奔终点的搞法会翻车吗？**绝对不会。**
当 A* 顺着终点方向冲进死胡同被墙挡住时，由于无法前进，绕路的代价会导致它的 $g$ 值开始飙升，连带着 $f$ 值变大。当死胡同里的总分变高到一定程度后，队列中原本那些“被冷落的绕路分叉点”就会重新变成最小点。A* 就会非常聪明地“认怂”，乖乖回头去试别的路。

#### 四、 总结一览表

| 特性           | Dijkstra 算法                                                | A* 算法                                                      |
| :------------- | :----------------------------------------------------------- | :----------------------------------------------------------- |
| **核心驱动力** | 盲目探索（仅靠已发生代价 $g$）                               | 启发式探索（已发生 $g$ + 预估未来 $h$）                      |
| **搜索方向性** | 无方向，360° 向外辐射                                        | 强方向性，直奔终点                                           |
| **遍历节点数** | **极多**（要把周围全部铺满）                                 | **极少**（只遍历趋向终点的骨干节点）                         |
| **最优解保证** | 必然是最短路径                                               | 只要 $h(n) \le \text{真实距离}$，必然是最短路径              |
| **适用场景**   | 1. 终点不固定（单源最短路径）2. 没有任何空间几何信息（拓扑图） | 1. 终点明确（点对点寻路）2. 有明确的空间坐标体系（游戏、地图） |

Dijkstra 走的是“绝对稳妥但极度浪费”的求实路线，而 A* 是在**保证绝对稳妥的前提下，利用几何常识（启发函数）把浪费降到最低**的降维优化。当 $h(n) = 0$ 时，A* 完美退化为 Dijkstra。

### Floyd算法

Floyd 算法是一种用于寻找给定的加权图中**任意两点之间最短路径（All-Pairs Shortest Paths）**的经典动态规划算法。

与 A* 或 Dijkstra 这种“点对点”或“单源”寻路算法不同，Floyd 算法属于“全员大练兵”——只要运行一次，图里**任意两个点之间的最短距离**就全算出来了。

#### 一、 核心思想：借道（动态规划）

Floyd 算法的本质是**动态规划**。

假设我们要找从节点 $A$ 到节点 $B$ 的最短路径。Floyd 的核心逻辑是：我直接走 $A \to B$ 是一种选法，但我如果**找一个中间节点 $K$ 进行“借道”**，走 $A \to K \to B$，路径会不会变得更短？

##### 核心状态转移方程

$$D[i][j] = \min(D[i][j], D[i][k] + D[k][j])$$

* **$D[i][j]$**：当前算出来的从节点 $i$ 到节点 $j$ 的最短距离。
* **$D[i][k] + D[k][j]$**：从 $i$ 先走到中间点 $k$，再从 $k$ 走到 $j$ 的总距离。
* **$\min(\dots)$**：比较“直达（或当前的方案）”和“绕道 $k$”哪个更近，永远选择更近的那条路来更新地图。

算法会**让 $K$ 遍历图中的每一个节点**。当所有节点都充当过一次“中间借道点”之后，图中任意两点的最短距离就被彻底锁定了。

#### 二、 三层循环

Floyd 算法的代码结构非常简单、优雅，甚至有些“暴力”，它的核心就是**三层嵌套的 `for` 循环**：

```cpp
// 伪代码示例：V 为顶点总数，matrix 为邻接矩阵
for (int k = 0; k < V; k++) {          // 第一层：中间借道点 k
    for (int i = 0; i < V; i++) {      // 第二层：起点 i
        for (int j = 0; j < V; j++) {  // 第三层：终点 j
            // 如果通过 k 借道可以让 i 到 j 的距离更短，则松弛（更新）距离
            if (matrix[i][k] + matrix[k][j] < matrix[i][j]) {
                matrix[i][j] = matrix[i][k] + matrix[k][j];
            }
        }
    }
}
```

**必须把遍历中间点 $k$ 的循环放在最外层！** 如果把 $k$ 放在内层，算法在还没有推导完所有局部最优解时就会草率跳过，导致最终算出来的路径不是全局最短。

#### 三、 Floyd 算法的优缺点

##### 优点：

1. **全点对寻路**：一步到位，算完之后你想查哪两点之间的距离，直接查 $D[i][j]$ 邻居矩阵，时间复杂度为 $O(1)$。
2. **支持负权重边**：Dijkstra 和 A* 算法在遇到边权为负数（比如走这条路不仅不累，还能回血）时会翻车，而 Floyd 算法能够完美支持**负权边**（但图里不能有“负权回路/死循环回血”）。
3. **代码极简**：没有复杂的优先队列、没有 Open/Close 表，只有三层 `for` 循环，极难写错。

##### 缺点：

1. **时间复杂度极高**：因为是三层完全遍历，时间复杂度是稳定的 $O(V^3)$（$V$ 为顶点数）。如果图里有 1000 个点，就要计算 $1000^3 = 10$ 亿次，节点一多直接卡死。
2. **空间复杂度大**：需要一个 $O(V^2)$ 的二维矩阵来死记硬背所有点对点的距离。

### [P2910 [USACO08OPEN] Clear And Present Danger S](https://www.luogu.com.cn/problem/P2910)

```c++
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    // 找宝藏的路径
    vector<int> path(m);
    for (int i = 0; i < m; ++i) {
        // 序号从 1 开始
        cin >> path[i];
        // 序号从 0 开始
        path[i]--;
    }

    vector<vector<int>> distance(n, vector<int>(n, 0x7fffffff));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            cin >> distance[i][j];

    for (int k = 0; k < n; ++k)
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                if (distance[i][k] != 0x7fffffff
                    && distance[k][j] != 0x7fffffff
                    && distance[i][j] > distance[i][k] + distance[k][j])
                    distance[i][j] = distance[i][k] + distance[k][j];

    int res = 0;
    for (int i = 0; i + 1 < m; ++i)
        res += distance[path[i]][path[i + 1]];
    cout << res;
}
```

### Bellman-Ford（贝尔曼-福特）算法

如果说 Dijkstra 是一个**只能顺境作战的精英**，那 Bellman-Ford 算法就是一个**能够在逆境中死磕的硬汉**。

Bellman-Ford 算法是一种用于求解**单源最短路径**的经典算法。它的核心工程定位非常明确：**专门为了解决 Dijkstra 无法处理的“负权边”问题而生，并且能够敏锐地侦测出图中的“负权回路（死循环回血陷阱）”。**

#### 一、 核心思想：暴力流的“全面松弛”

与 Dijkstra 算法每一步都要精挑细选“当前哪一步最近”的贪心策略不同，Bellman-Ford 的思想极其朴实无华，甚至有点暴力：**对图中的所有边，进行多轮无差别的“松弛”操作。**

##### 什么是松弛？
所谓松弛，就是利用三角不等式去尝试更新最短距离。对于一条从节点 $u$ 走向节点 $v$ 且权重为 $w$ 的边：
$$\text{if } D[u] + w < D[v] \text{ then } D[v] = D[u] + w$$
它的逻辑是：“如果我从起点先走到 $u$，再通过这条边走到 $v$，比我直接到 $v$ 的当前方案更近，那我就更新 $v$ 的最短距离。”

##### 为什么要循环 $V-1$ 轮？（$V$ 为顶点总数）
在一个含有 $V$ 个顶点的图中，任意两点之间的最短路径**最多只能包含 $V-1$ 条边**（如果超过 $V-1$ 条边，说明路径中一定出现了重复的节点，即走进了环路）。

Bellman-Ford 算法每一轮循环，都会把全图**所有的边**全部尝试松弛一遍。
* 第一轮全面松弛后，所有距离起点只有 1 条边的节点的最短路径一定能被确定。
* 第二轮全面松弛后，所有距离起点有 2 条边的节点的最短路径一定能被确定。
* 依此类推……当循环完 $V-1$ 轮后，全图所有节点的最短路径就应该全部被锁定了。

#### 二、 算法执行机制与代码结构

Bellman-Ford 的代码结构非常简单直观，主要分为两个阶段：

```cpp
// 阶段一：初始化起点
for (int i = 0; i < V; i++) dist[i] = INF;
dist[start] = 0;

// 阶段二：进行 V-1 轮全面松弛
for (int i = 1; i <= V - 1; i++) {
    for (Edge edge : edges) { // 遍历图中的“每一条边”
        if (dist[edge.u] != INF && dist[edge.u] + edge.w < dist[edge.v]) {
            dist[edge.v] = dist[edge.u] + edge.w;
        }
    }
}

// 阶段三：第 V 轮检测，专门揪出负权回路
bool hasNegativeCycle = false;
for (Edge edge : edges) {
    if (dist[edge.u] != INF && dist[edge.u] + edge.w < dist[edge.v]) {
        // 如果在第 V 轮，距离还能被更新，说明图里有负权回路！
        hasNegativeCycle = true; 
        break;
    }
}
```

#### 三、 终极武器：如何检测“负权回路”？

这是 Bellman-Ford 算法最无可替代的特性。

- **什么是负权回路**：如果图里存在一个环，环上所有边的权重加起来是个**负数**（比如 $A \to B \to C \to A$ 的总代价是 $-5$）。那算法只要在这个环里无限转圈，路径代价就能无限减小到负无穷（$-\infty$）。
- **如何检测**：前面说了，正常的最短路径最多只有 $V-1$ 条边。如果算法跑完 $V-1$ 轮后，我们**再跑第 $V$ 轮全面松弛**，发现竟然还有节点的距离能够被更新（变短），那就说明图里一定存在负权回路。此时算法会直接报错拦截，告诉你：“这图有逻辑漏洞，无法计算最短路径！”

#### 四、 寻路算法大决战

现在，图论中的四大经典寻路算法全部集结：

| **特性**         | **A\* 算法**               | **Dijkstra 算法**      | **Bellman-Ford 算法**     | **Floyd 算法**                 |
| ---------------- | -------------------------- | ---------------------- | ------------------------- | ------------------------------ |
| **解决的问题**   | **点对点**最短路径         | **单源**最短路径       | **单源**最短路径          | **多源**最短路径（全图全点对） |
| **核心机制**     | 启发式空间剪枝             | 贪心扩展最近点         | **全边 $V-1$ 轮全面松弛** | 三层 `for` 循环迭代借道        |
| **时间复杂度**   | 极快（最优可达 $O(V)$）    | $O(E \log V)$ （较快） | $O(V \cdot E)$ （较慢）   | $O(V^3)$ （极慢）              |
| **负权边支持**   | 不支持                     | 不支持                 | **完美支持**              | **完美支持**                   |
| **负权环检测**   | 无法检测（会死循环）       | 无法检测（会选错路）   | **能精准检测并报错**      | 能检测，但处理较麻烦           |
| **空间几何依赖** | 极度依赖（需要坐标算 $h$） | 不需要                 | 不需要                    | 不需要                         |

##### 核心优缺点对比

- **优点**：极其强悍的容错率。不管是正权边、负权边，它全都能算，并且自带 debug 属性（检测负权环）。由于它不关心拓扑结构，只对边列表做遍历，非常适合进行分布式计算（网络路由协议中的距离矢量协议 RIP 就是基于 Bellman-Ford 实现的）。
- **缺点**：速度太慢。因为每轮都要盲目遍历所有的边 $E$，总共要跑 $V-1$ 轮，在密集图里它的计算量远大于 Dijkstra。

> **工程优化提示（SPFA 算法）**：
>
> 在实际编写代码时，如果嫌 Bellman-Ford 太慢，业界通常会使用它的队列优化版本——**SPFA（Shortest Path Faster Algorithm）**。SPFA 的核心思想是：“只有在上一轮中被更新了距离的节点，它的邻居才有可能在下一轮被更新。”因此用一个队列来只存放被更新过的节点，从而将平均时间复杂度优化到 $O(k \cdot E)$（$k$ 是一个小常数）。

### [787. K 站中转内最便宜的航班](https://leetcode.cn/problems/cheapest-flights-within-k-stops/)

```c++
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

class Solution {
public:
    // 阉割版 Bellman-Ford
    int findCheapestPrice(int n, vector<vector<int>> &flights, int src, int dst, int k) {
        vector<int> cur(n, INT_MAX);
        cur[src] = 0;
        for (int i = 0; i <= k; ++i) {
            vector<int> nxt(cur);
            for (const auto &edge: flights) {
                if (cur[edge[0]] == INT_MAX) continue;
                // 从旧表中取数据更新，标准的 Bellman—Ford 是从新表中取
                nxt[edge[1]] = min(nxt[edge[1]], cur[edge[0]] + edge[2]);
            }
            cur = nxt;
        }
        return cur[dst] == INT_MAX ? -1 : cur[dst];
    }
};
```

### [P3385 【模板】负环](https://www.luogu.com.cn/problem/P3385)

```c++
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

int n, m, T;
const int MAX_VAL = 0x7fffffff;

// 链式前向星
vector<int> head;
vector<int> nxt;
vector<int> to;
vector<int> weight;
int cnt;

void initGraph() {
    // 点的下标从 1 开始
    head.resize(n + 1, 0);
    nxt.resize((m << 1) + 1);
    to.resize((m << 1) + 1);
    weight.resize((m << 1) + 1);
    fill(begin(head), end(head), 0);
    cnt = 1;
}

void addEdge(int u, int v, int w) {
    nxt[cnt] = head[u];
    to[cnt] = v;
    weight[cnt] = w;
    head[u] = cnt;
    cnt++;
}

// Bellman-Ford
// 从 1 到各个点的最短距离
vector<int> distances;
// 存放上一轮松弛中有变动的点
queue<int> q;
// 是否在队列中
vector<bool> enter;
// 记录点的松弛次数
vector<int> updateCnt;

void initBellmanFord() {
    distances.resize(n + 1, MAX_VAL);
    enter.resize(n + 1, false);
    updateCnt.resize(n + 1, 0);
    fill(begin(distances), end(distances), MAX_VAL);
    fill(begin(enter), end(enter), false);
    fill(begin(updateCnt), end(updateCnt), 0);
}

void clearQueue() {
    queue<int> empty;
    swap(q, empty);
}

// 从顶点 1 出发是否能到达负环
bool hasNegativeCircle() {
    distances[1] = 0;
    updateCnt[1]++;
    q.emplace(1);
    enter[1] = true;

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        enter[u] = false;
        for (int ei = head[u]; ei > 0; ei = nxt[ei]) {
            int v = to[ei];
            int w = weight[ei];
            // 没法松弛就跳过
            if (distances[v] <= distances[u] + w) continue;
            distances[v] = distances[u] + w;
            // 在队列就跳过
            if (enter[v]) continue;
            // 到 v 点的路径被松弛了一次
            updateCnt[v]++;
            if (updateCnt[v] >= n) return true;
            q.emplace(v);
            enter[v] = true;
        }
    }
    return false;
}

int main() {
    cin >> T;
    // 每组测试用例
    for (int i = 0; i < T; ++i) {
        cin >> n >> m;
        // 初始化
        initGraph();
        initBellmanFord();
        clearQueue();
        // 建图
        for (int j = 0, u, v, w; j < m; ++j) {
            cin >> u >> v >> w;
            if (w >= 0) {
                addEdge(u, v, w);
                addEdge(v, u, w);
            } else {
                addEdge(u, v, w);
            }
        }
        cout << (hasNegativeCircle() ? "YES" : "NO") << endl;
    }
}
```
