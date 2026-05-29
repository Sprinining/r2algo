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

## Floyd 算法

Floyd 算法是一种用于解决所有节点对之间最短路径问题的算法。它通过动态规划的思想，逐步计算出所有节点对之间的最短路径。

Floyd 算法使用一个二维数组 distance 来记录节点对之间的最短距离。初始时，distance\[i\]\[j\] 表示节点 i 到节点 j 的直接距离（如果存在边），否则为无穷大。算法通过三重循环不断更新 distance 数组，最终得到所有节点对之间的最短路径。

Floyd 算法的核心思想是动态规划。外层循环控制中间节点 k，内层两个循环分别遍历起点 i 和终点 j。如果通过节点 k 可以使 i 到 j 的距离更短，则更新 distance\[i\]\[j\]。重复此过程，直到所有节点都被遍历过。

diatance\[i\]\[j\] 表示 i 和 j 的最短距离，更新：`distance[i][j] = min(distance[i][j], distance[i][k] + distance[k][j])`

- 时间复杂度：`O(n^3)`，空间复杂度：`O(n^2)`，常数时间小，容易实现
- 不适用于存在负环的图

```c++
int main() {
    // n * n 的矩阵
    int n = 10;
    // 其实就是带权图的邻接矩阵
    vector<vector<int>> distance(n, vector<int>(n, INT_MAX));
    
    // 省略 distance 根据给出的边进行初始化
    
    // i 经过 k 到达 j
    for (int k = 0; k < n; ++k)
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                if (distance[i][k] != INT_MAX
                    && distance[k][j] != INT_MAX
                    && distance[i][j] > distance[i][k] + distance[k][j])
                    distance[i][j] = distance[i][k] + distance[k][j];
}
```

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

## Bellman-Ford 算法

解决==可以有负边但不能有负环==的图，求单源最短路径的算法。

**Bellman-Ford 过程**：每一轮考察每条边，每条边都尝试进行松弛操作，那么若干点的 distance 会变小。当某一轮发现不再有松弛操作出现时，算法停止。

**Bellman-Ford 算法时间复杂度**：假设点的数量为 N，边的数量为 M，每一轮时间复杂度 O(M)。最短路存在的情况下，因为 1 次松弛操作会使 1 个点的最短路的边数 +1。而从源点出发到任何点的最短路最多走过全部的 n 个点，所以松弛的轮数必然 <= n - 1。所以Bellman-Ford算法时间复杂度 O(M*N)

**重要推广**：==判断从某个点出发能不能到达负环==。上面已经说了，如果从A出发存在最短路（没有负环），那么松弛的轮数必然 <= n - 1。而如果从A点出发到达一个负环，那么松弛操作显然会无休止地进行下去。所以，如果发现从A点出发，在第n轮时松弛操作依然存在，说明从A点出发能够到达一个负环。可以通过设置一个虚拟源点（与原来所有的点都有连接），==判断图是否有负环==。

### ChatGPT 给出的介绍

Bellman-Ford 算法的关键思想是通过**多次松弛操作**（relaxation）逐步逼近每个顶点的最短路径，最终在迭代结束时，能够正确确定从源点到所有点的最短路径。要理解为什么每一轮松弛能确定一些点的最短距离，可以从以下几个方面解释：

#### 1. 松弛操作的定义

松弛操作的过程是通过检查从某一顶点到另一顶点之间的边，看看是否可以通过这个顶点找到一条更短的路径。如果可以，那么就更新目标顶点的最短距离。

对于每条边 (u, v) ，如果：`dist[v] > dist[u] + weight(u, v)`
那么就更新：`dist[v] = dist[u] + weight(u, v)`

#### 2. 多轮松弛的作用

假设图中有 V 个顶点，最坏情况下，==从源点到一个顶点的最短路径可能包含最多 V - 1 条边==。因此，Bellman-Ford 算法执行 V - 1 ==轮==松弛操作，确保可以找到源点到任意顶点的最短路径。

每一轮松弛都会检查所有边，并尝试通过更短的路径更新节点的最短距离。对于一条最短路径上恰好有 k 条边的节点，==最多==需要 k 轮松弛来确定该节点的最短距离。

#### 3. 每轮松弛确定某些点的最短距离

==在第 i 轮松弛中，Bellman-Ford 算法会确保从源点到任何节点的最短路径最多经过 i 条边==。因此，经过 i 轮松弛后，所有最短路径包含 i 条或更少边的节点的最短距离都会被确定。随着轮数的增加，更多节点的最短路径距离会被确定。

特别是，当执行到第 V - 1 轮时，所有节点的最短距离都会被确定，因为最长的简单路径（不包含环）最多包含  V - 1 条边。

#### 4. 确定最短路径

通过多次松弛操作，Bellman-Ford 算法最终能保证：
- 如果某个点的最短路径被更新为一个值，那么这个值是正确的，因为此时它已经不能通过任何进一步的松弛获得更短的路径。
- 所以，每一轮松弛后，至少有一些点的最短距离是最终值，不会再发生变化。

#### 5. 总结

每一轮松弛都能确定一部分节点的最短路径，因为它==逐渐考虑到从源点到每个节点经过不同数量边的路径==。经过最多 V - 1 轮后，所有点的最短路径都会被确定。因此，每一轮松弛后，某些点的最短路径是最终的且不会再改变。

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
