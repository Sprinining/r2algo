### Dijkstra 算法

Dijkstra（迪杰斯特拉）算法是图论中用于解决**单源最短路径**问题的经典贪心算法。以下是基于**普通堆（小根堆）**实现的 Dijkstra 算法的详细介绍。

#### 1. 算法概述与核心限制

* **基本定义**：Dijkstra 算法用于计算图中一个源节点到其他所有节点的最短路径。
* **时间复杂度**：$O(m \times \log m)$，其中 $m$ 为图中的边数。在最坏情况下，每条边都可能触发一次入堆操作，堆的最大大小为 $m$。
* **局限性（致命缺点）**：**Dijkstra 算法不能处理边带有负权的情况**。
    * *原因*：Dijkstra 算法的核心是贪心策略，它假设“当前从小根堆中弹出的最短距离节点，其距离已经不可能更短了”。如果图中存在负权边，后面未访问的路径在加上负权后可能会变得比当前弹出的距离更短，从而破坏贪心的正确性。

#### 2. 核心数据结构

为了高效地找到当前距离最短的节点并更新邻居，算法需要维护以下三个关键数据结构：

1.  **距离数组 `distance[]`**：
    * `distance[i]` 表示当前从源点到 $i$ 号节点已知的最短距离。
    * 初始时，`distance[源点] = 0`，其余所有节点的距离均设为无穷大。
2.  **状态数组 `visited[]`**：
    * `visited[i]` 表示 $i$ 号节点**是否从小根堆中弹出过**。
    * 一旦 `visited[i] == true`，说明源点到 $i$ 号节点的最短路径已经最终确定，之后不再对其进行处理。
3.  **小根堆（优先队列）**：
    * 堆中存放的记录格式为：`(x 点, 源点到 x 的当前距离)`。
    * 堆严格根据**距离**从小到大进行自动排序。

#### 3. 算法执行步骤

算法的整体流程可以概括为：**初始化 -> 堆弹出 -> 邻边松弛 -> 循环直至堆空**。

##### 第一步：初始化
* 令 `distance[源点] = 0`，其余节点的 `distance` 设为 $\infty$。
* 将二元组 `(源点, 0)` 压入小根堆。
* 所有的 `visited` 状态初始设为 `false`。

##### 第二步：循环提取与松弛（直至小根堆为空）
从小根堆中弹出当前距离最小的记录，假设弹出的记录为 `(u 点, 源点到 u 的距离)`，随后进入条件分支判断：

###### a. 如果 `visited[u] == true`
* 说明 $u$ 点在之前已经以更短的距离被弹出并处理过了（堆中存在旧的、距离较长的冗余记录）。
* **处理方式**：直接跳过，啥也不做，立即重复步骤 2（弹出下一个）。

###### b. 如果 `visited[u] == false`
* 说明这是 $u$ 点第一次被弹出，此时的 `distance[u]` 就是源点到 $u$ 点的最终最短距离。
* **处理方式**：
    1.  令 `visited[u] = true`，标记 $u$ 点已确定。
    2.  **考察 $u$ 的每一条邻边**：假设当前遍历到的某条边去往 $v$ 点，该边的边权为 $w$。
        * **检查是否可以松弛**：如果 `visited[v] == false`（$v$ 未确定）**并且** `distance[u] + w < distance[v]`。
        * **执行松弛与入堆**：更新 $v$ 的最短距离，令 `distance[v] = distance[u] + w`，并将新记录 `(v, distance[u] + w)` 压入小根堆。
    3.  处理完 $u$ 的所有邻边后，重复步骤 2。

##### 第三步：算法结束
当小根堆变为空时，整个计算过程结束。此时 `distance[]` 数组中存储的值就是源点到图中各个可达节点的最短路径长度。

#### 4. 算法特性总结

* **贪心本质**：每一轮都从小根堆中选择当前“最近”的未访问节点 $u$。因为图中所有边权均为正数，所以不可能通过其他未访问的节点绕路回到 $u$ 却得到更短的路径。
* **空间复杂度**：$O(n + m)$。需要存储图的结构（邻接表）、`distance` 与 `visited` 数组（大小为点数 $n$），以及小根堆的空间（最大可达边数 $m$）。



### 基于反向索引堆的 Dijkstra 算法

在图论中，Dijkstra 算法的效率很大程度上取决于**优先队列（堆）**的性能。从“普通堆”走向“反向索引堆”，是算法效率和空间利用率的一次重大升级。

#### 1. 核心痛点：为什么要引入反向索引堆？

在**普通堆**的实现中，堆内可能会同时存在多个关于同一个点 $v$ 的记录（例如 `(v, 10)` 和 `(v, 7)`）。这是因为普通堆**无法定位和修改**已经在堆内部的元素，只能采取“直接将新记录压入堆中”的妥协方案。

这导致了两个问题：
1. **空间浪费**：堆的体积膨胀到了边数 $m$，导致堆操作的时间复杂度变为 $O(\log m)$。
2. **无效操作**：弹出元素时，必须依赖 `visited` 数组来过滤掉那些早该被淘汰的旧记录（冗余记录）。

##### 反向索引堆的解决方案
反向索引堆在传统的“**元素数组（存储点和距离）**”基础上，引入了一张**反向索引表**。
* **作用**：记录每个节点 $u$ 当前在堆底层的结构数组中的**具体下标位置**。
* **效果**：通过反向索引表，算法可以实现 $O(1)$ 时间找到堆内的指定节点，并直接修改它的距离（$d$ 信息），随后进行向上（HeapifyUp）或向下（HeapifyDown）的堆调整。

因此，**堆内存放的记录永远不会超过 $n$ 个（节点数）**，每次调整堆的时间复杂度降低为 $O(\log n)$。

#### 2. 核心状态与数据结构

使用反向索引堆后，我们不再需要单独的 `visited` 数组，而是通过节点在反向索引堆中的**三种状态**来决定后续操作：

1. **从未进入过堆**：说明该点尚未被探索。
2. **正在堆中**：说明该点已被探索，但最短路径尚未最终确定，距离仍有被“松弛（变小）”的可能。
3. **已经从堆中弹出**：说明该点的最短路径已最终确定，之后无论如何都不再处理。

#### 3. 算法执行步骤

整体流程保持连贯，核心在于邻边的**动态分类讨论**：

##### 第一步：初始化
* 将源点及初始距离加入反向索引堆，即 `(源点, 0)`。
* 此时源点在堆中的状态变为“正在堆中”，其余点为“从未进入过堆”。

##### 第二步：循环提取与动态调整（直至堆为空）
从反向索引堆中弹出当前距离最小的记录 `(u, 源点到 u 的距离)`。此时 $u$ 的最终最短距离已确定（状态变为“已弹出”）。

随后，**考察 $u$ 的每一条邻边**。假设某条边去往 $v$ 点，边权为 $w$，预估的新距离为 `new_dist = distance[u] + w`：

* **情况 a：如果 $v$ 从未进入过反向索引堆**
  * 说明第一次发现 $v$ 点。
  * **操作**：直接向反向索引堆中**新增**一条记录 `(v, new_dist)`。
* **情况 b：如果 $v$ 曾经从反向索引堆弹出过**
  * 说明 $v$ 的最短路径早已确定。
  * **操作**：直接**忽略**，跳过。
* **情况 c：如果 $v$ 当前正在反向索引堆里**
  * 说明找到了到达 $v$ 的另一条可能路径。
  * **操作**：对比 `new_dist` 与 $v$ 在堆中的当前距离。如果 `new_dist` 更小，则直接在堆中**修改** $v$ 的距离，并触发堆调整（同时更新反向索引表）；如果变大或相等，则**跳过**。

##### 第三步：结束
处理完 $u$ 的每条边后，重复步骤二。当反向索引堆为空时，过程结束。最终的 `distance` 记录了源点到每个可达点的最终最短距离。

#### 4. 两种实现方案对比

| 特性               | 普通堆实现                         | 反向索引堆实现                                 |
| :----------------- | :--------------------------------- | :--------------------------------------------- |
| **时间复杂度**     | $O(m \times \log m)$               | $O(m \times \log n)$                           |
| **堆内最大元素量** | $m$ （存在大量历史冗余记录）       | $n$ （每个节点在堆中最多只有一条记录）         |
| **空间利用率**     | 较低（随边数膨胀）                 | 极高（严格受限于节点数）                       |
| **去重依赖**       | 必须依赖额外的 `visited` 数组过滤  | 依赖反向索引表的状态直接判断                   |
| **适用场景**       | 稀疏图，或支持快速语言原生堆的场景 | 稠密图（$m \gg n$ 时），对性能有极致要求的场景 |

###  基于反向索引堆优化的 Dijkstra 与 Prim 算法

Dijkstra 算法（求最短路径）与 Prim 算法（求最小生成树）在引入**反向索引堆（Index Min Heap）**后，两者的执行流程和优化逻辑表现出了高度的对称性，时间复杂度双双进化为 O(m * logn)。

#### 1. 核心机制对比

虽然解决的问题不同，但两者引入反向索引堆的**核心目的完全一致**：消除堆内的冗余历史记录，将堆的最大体积从边数 m 压缩到节点数 n。

| 对比维度             | Dijkstra 算法优化                                            | Prim 算法优化                                                |
| :------------------- | :----------------------------------------------------------- | :----------------------------------------------------------- |
| **解决问题**         | 单源最短路径（SSSP）                                         | 最小生成树（MST）                                            |
| **堆内元素含义**     | 存放 (u, d)，d 为源点到 u 的**全局路径总长**。               | 存放 (u, d)，d 为当前生成树到外围点 u 的**单条边权**。       |
| **普通堆的痛点**     | 随着路径松弛，同一个点会以不同的路径长度多次入堆，积压大量废弃冗余。 | 随着新点入树，同一个外围点会被多条邻边解锁，导致多条边权记录同时在堆中。 |
| **反向索引堆的改变** | 发现更短路径时，利用反向索引表 O(1) 定位，**直接修改**堆内旧值并动态调整。 | 发现更短邻边时，利用反向索引表 O(1) 定位，**直接修改**堆内旧值并动态调整。 |
| **优化前后复杂度**   | O(m * logm) -> O(m * logn)                                   | O(m * logm) -> O(m * logn)                                   |
| **边权限制**         | 严格要求边权**不能为负**（因贪心策略基于全局累加变长）。     | 对边权正负**无严格限制**（割边定理只要求选当前最小边）。     |

#### 2. 邻边动态分类讨论的逻辑对仗

当从反向索引堆中弹出当前权值最小的节点 u 后，两个算法在考察邻边 (u, v, w) 时的控制逻辑几乎完全相同。反向索引表将目标点 v 的状态精确划分为三种：

##### 情况 A：目标点 v 从未进入过堆
* **Dijkstra**：第一次发现点 v。更新 `distance[v] = distance[u] + w`，并将 `(v, distance[v])` **新增**入堆。
* **Prim**：第一次发现点 v。更新 `closest_edge[v] = w`，并将 `(v, w)` **新增**入堆。

##### 情况 B：目标点 v 已经从堆中弹出
* **Dijkstra**：点 v 的最短路径已确定。直接**忽略**。
* **Prim**：点 v 已经并入最小生成树内部。直接**忽略**。

##### 情况 C：目标点 v 当前正在堆中（核心优化点）
* **Dijkstra**：对比新路径 `distance[u] + w` 与堆内旧路径 `distance[v]`。如果新路径更短，利用反向索引**直接修改**堆内数值并向上调整（Heapify Up）。
* **Prim**：对比新边权 w 与堆内旧边权 `closest_edge[v]`。如果新边权更小，利用反向索引**直接修改**堆内数值并向上调整（Heapify Up）。

### [P4779 【模板】单源最短路径（标准版）](https://www.luogu.com.cn/problem/P4779)

- 普通堆

```c++
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

struct cmp {
    bool operator()(pair<int, int> &p1, pair<int, int> &p2) {
        return p1.second > p2.second;
    }
};

int main() {
    int n, m, s;
    cin >> n >> m >> s;

    vector<vector<pair<int, int>>> graph(n + 1);
    // 建图
    for (int i = 0, u, v, w; i < m; ++i) {
        cin >> u >> v >> w;
        graph[u].emplace_back(make_pair(v, w));
    }

    // 标记是否从堆中弹出过
    vector<bool> visited(n + 1, false);
    priority_queue<pair<int, int>, vector<pair<int, int>>, cmp> heap;
    vector<int> distances(n + 1, 0x7fffffff);
    // 源点入堆
    heap.emplace(make_pair(s, 0));
    distances[s] = 0;

    while (!heap.empty()) {
        auto top = heap.top();
        heap.pop();
        int u = top.first;
        if (visited[u]) continue;
        visited[u] = true;
        for (const auto &item: graph[u]) {
            int v = item.first;
            int w = item.second;
            if (visited[v]) continue;
            if (distances[v] > distances[u] + w) {
                distances[v] = distances[u] + w;
                heap.emplace(make_pair(v, distances[v]));
            }
        }
    }

    for (int i = 1; i <= n; ++i)
        cout << distances[i] << " ";
}
```

- 反向索引堆

```c
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n, m, s;

// 链式前向星
vector<int> head;
vector<int> nxt;
vector<int> to;
vector<int> weight;
int cnt;

void initGraph() {
    // 点的编号从 1 开始
    // resize 只会将新增的位置设置为新的值
    head.resize(n + 1, 0);
    fill(head.begin(), head.end(), 0);
    nxt.resize(m + 1);
    to.resize(m + 1);
    weight.resize(m + 1);
    // 边的编号从 1 开始
    cnt = 1;
}

void addEdge(int u, int v, int w) {
    nxt[cnt] = head[u];
    to[cnt] = v;
    weight[cnt] = w;
    head[u] = cnt;
    cnt++;
}

vector<int> heap;
int heapSize;
// 反向索引表
// where[v] = -2，表示v这个节点，已经弹出过了
// where[v] = -1，表示v这个节点，从来没有进入过堆
// where[v] = i(>=0)，表示 v 这个节点，在堆上的 i 位置
// 所有 where 的 set 操作都包含在堆的操作中
vector<int> where;
// 记录源点到目标点的最短距离
// 所有 distances 的 set 操作与堆的操作分离
vector<int> distances;

void initHeap() {
    heap.resize(n);
    heapSize = 0;
    // 初始状态都没进过堆
    where.resize(n + 1, -1);
    fill(where.begin(), where.end(), -1);
    // 初始最短距离都是无穷大
    distances.resize(n + 1, 0x7fffffff);
    fill(distances.begin(), distances.end(), 0x7fffffff);
}

// 自顶向下调整堆
void adjustHeapTopDown(int curIndex) {
    auto temp = heap[curIndex];
    int leftChildIndex = 2 * curIndex + 1;
    while (leftChildIndex <= (heapSize - 1)) {
        if ((leftChildIndex < heapSize - 1)
            && distances[heap[leftChildIndex]] > distances[heap[leftChildIndex + 1]])
            leftChildIndex++;
        if (distances[heap[leftChildIndex]] >= distances[temp]) break;
        heap[curIndex] = heap[leftChildIndex];
        // 修改反向索引表
        where[heap[leftChildIndex]] = curIndex;
        curIndex = leftChildIndex;
        leftChildIndex = 2 * curIndex + 1;
    }
    heap[curIndex] = temp;
    // 修改反向索引表
    where[temp] = curIndex;
}

// 自下而上调整堆
void adjustHeapBottomUP(int curIndex) {
    auto temp = heap[curIndex];
    int parentIndex = (curIndex - 1) / 2;
    while (parentIndex >= 0) {
        if (distances[heap[parentIndex]] <= distances[temp]) break;
        heap[curIndex] = heap[parentIndex];
        // 修改反向索引表
        where[heap[parentIndex]] = curIndex;
        curIndex = parentIndex;
        if (curIndex == 0) break;
        parentIndex = (curIndex - 1) / 2;
    }
    heap[curIndex] = temp;
    // 修改反向索引表
    where[temp] = curIndex;
}


void addToHeap(int v) {
    heap[heapSize] = v;
    heapSize++;
    adjustHeapBottomUP(heapSize - 1);
}

int getTop() {
    int res = heap[0];
    heap[0] = heap[heapSize - 1];
    heapSize--;
    adjustHeapTopDown(0);
    where[res] = -2;
    return res;
}

void addOrUpdateOrIgnore(int v, int d) {
    if (where[v] == -2) {
        return;
    } else if (where[v] == -1) {
        distances[v] = d;
        // v 不在堆中，新增记录
        addToHeap(v);
    } else if (where[v] >= 0) {
        // 经过 u 点到达 v 点能使源点到达 v 点距离更短，就更新
        if (distances[v] > d) {
            distances[v] = d;
            // 修改堆中原有的那条，再向上调整（距离变短，只需要往上调整）
            adjustHeapBottomUP(where[v]);
        }
    }
}

int main() {
    cin >> n >> m >> s;

    // 建图
    initGraph();
    for (int i = 0, u, v, w; i < m; ++i) {
        cin >> u >> v >> w;
        addEdge(u, v, w);
    }

    initHeap();
    addOrUpdateOrIgnore(s, 0);

    while (heapSize > 0) {
        int u = getTop();
        for (int edge = head[u]; edge != 0; edge = nxt[edge])
            addOrUpdateOrIgnore(to[edge], distances[u] + weight[edge]);
    }

    for (int i = 1; i <= n; ++i)
        cout << distances[i] << " ";
}
```

### [743. 网络延迟时间](https://leetcode.cn/problems/network-delay-time/)

- 普通堆

```c++
#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <queue>

using namespace std;

class Solution {
public:

    struct cmp {
        bool operator()(pair<int, int> &p1, pair<int, int> &p2) {
            return p1.second > p2.second;
        }
    };

    // 节点编号从 1 开始
    int networkDelayTime(vector<vector<int>> &times, int n, int k) {
        // 邻接表建图
        vector<vector<pair<int, int>>> graph(n + 1);
        for (const auto &item: times)
            graph[item[0]].emplace_back(make_pair(item[1], item[2]));

        // 记录从源点到每个点的距离
        vector<int> distance(n + 1, INT_MAX);
        // 记录是否从堆中弹出过
        vector<int> visited(n + 1, false);
        // 小根堆：（u，源点到 u 的距离）
        priority_queue<pair<int, int>, vector<pair<int, int>>, cmp> heap;
        // k 到自身距离为 0
        heap.emplace(make_pair(k, 0));
        distance[k] = 0;

        while (!heap.empty()) {
            auto p = heap.top();
            heap.pop();
            int u = p.first;
            // 已经确定距离的不再处理
            if (visited[u] == true) continue;
            visited[u] = true;
            for (const auto &item: graph[u]) {
                int v = item.first;
                int w = item.second;
                // 已经确定距离的不再处理
                if (visited[v] == true) continue;
                // 尝试源点在经过 u 的情况下到达 v ，是否可以使到达 v 的距离缩短
                if (distance[v] > distance[u] + w) {
                    distance[v] = distance[u] + w;
                    // 这条边入堆
                    heap.emplace(v, distance[v]);
                }
            }
        }

        int res = 0;
        for (int i = 1; i <= n; ++i) {
            // 有的点到达不了
            if (distance[i] == INT_MAX) return -1;
            res = max(res, distance[i]);
        }
        return res;
    }
};
```

- 反向索引堆

```c++
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n, m, s;

// 链式前向星
vector<int> head;
vector<int> nxt;
vector<int> to;
vector<int> weight;
int cnt;

void initGraph() {
    // 点的编号从 1 开始
    // resize 只会将新增的位置设置为新的值
    head.resize(n + 1, 0);
    fill(head.begin(), head.end(), 0);
    nxt.resize(m + 1);
    to.resize(m + 1);
    weight.resize(m + 1);
    // 边的编号从 1 开始
    cnt = 1;
}

void addEdge(int u, int v, int w) {
    nxt[cnt] = head[u];
    to[cnt] = v;
    weight[cnt] = w;
    head[u] = cnt;
    cnt++;
}

vector<int> heap;
int heapSize;
// 反向索引表
// where[v] = -2，表示v这个节点，已经弹出过了
// where[v] = -1，表示v这个节点，从来没有进入过堆
// where[v] = i(>=0)，表示 v 这个节点，在堆上的 i 位置
// 所有 where 的 set 操作都包含在堆的操作中
vector<int> where;
// 记录源点到目标点的最短距离
// 所有 distances 的 set 操作与堆的操作分离
vector<int> distances;

void initHeap() {
    heap.resize(n);
    heapSize = 0;
    // 初始状态都没进过堆
    where.resize(n + 1, -1);
    fill(where.begin(), where.end(), -1);
    // 初始最短距离都是无穷大
    distances.resize(n + 1, 0x7fffffff);
    fill(distances.begin(), distances.end(), 0x7fffffff);
}

// 自顶向下调整堆
void adjustHeapTopDown(int curIndex) {
    auto temp = heap[curIndex];
    int leftChildIndex = 2 * curIndex + 1;
    while (leftChildIndex <= (heapSize - 1)) {
        if ((leftChildIndex < heapSize - 1)
            && distances[heap[leftChildIndex]] > distances[heap[leftChildIndex + 1]])
            leftChildIndex++;
        if (distances[heap[leftChildIndex]] >= distances[temp]) break;
        heap[curIndex] = heap[leftChildIndex];
        // 修改反向索引表
        where[heap[leftChildIndex]] = curIndex;
        curIndex = leftChildIndex;
        leftChildIndex = 2 * curIndex + 1;
    }
    heap[curIndex] = temp;
    // 修改反向索引表
    where[temp] = curIndex;
}

// 自下而上调整堆
void adjustHeapBottomUP(int curIndex) {
    auto temp = heap[curIndex];
    int parentIndex = (curIndex - 1) / 2;
    while (parentIndex >= 0) {
        if (distances[heap[parentIndex]] <= distances[temp]) break;
        heap[curIndex] = heap[parentIndex];
        // 修改反向索引表
        where[heap[parentIndex]] = curIndex;
        curIndex = parentIndex;
        if (curIndex == 0) break;
        parentIndex = (curIndex - 1) / 2;
    }
    heap[curIndex] = temp;
    // 修改反向索引表
    where[temp] = curIndex;
}


void addToHeap(int v) {
    heap[heapSize] = v;
    heapSize++;
    adjustHeapBottomUP(heapSize - 1);
}

int getTop() {
    int res = heap[0];
    heap[0] = heap[heapSize - 1];
    heapSize--;
    adjustHeapTopDown(0);
    where[res] = -2;
    return res;
}

void addOrUpdateOrIgnore(int v, int d) {
    if (where[v] == -2) {
        return;
    } else if (where[v] == -1) {
        distances[v] = d;
        // v 不在堆中，新增记录
        addToHeap(v);
    } else if (where[v] >= 0) {
        // 经过 u 点到达 v 点能使源点到达 v 点距离更短，就更新
        if (distances[v] > d) {
            distances[v] = d;
            // 修改堆中原有的那条，再向上调整（距离变短，只需要往上调整）
            adjustHeapBottomUP(where[v]);
        }
    }
}

class Solution {
public:
    int networkDelayTime(vector<vector<int>> &times, int N, int k) {
        n = N;
        m = times.size();
        s = k;

        // 建图
        initGraph();
        for (const auto &item: times)
            addEdge(item[0], item[1], item[2]);

        initHeap();
        addOrUpdateOrIgnore(s, 0);

        while (heapSize > 0) {
            int u = getTop();
            for (int edge = head[u]; edge != 0; edge = nxt[edge])
                addOrUpdateOrIgnore(to[edge], distances[u] + weight[edge]);
        }

        int res = 0;
        for (int i = 1; i <= n; ++i) {
            if (distances[i] == 0x7fffffff)
                return -1;
            res = max(res, distances[i]);
        }
        return res;
    }
};
```


### [1631. 最小体力消耗路径](https://leetcode.cn/problems/path-with-minimum-effort/)

```c++
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

class Solution {
public:
    struct cmp {
        bool operator()(vector<int> &v1, vector<int> &v2) {
            return v1[2] > v2[2];
        }
    };

    vector<int> move{-1, 0, 1, 0, -1};
    int rows, columns;

    bool isCoordinateLegal(int row, int column) {
        return row >= 0 && row < rows && column >= 0 && column < columns;
    }

    int minimumEffortPath(vector<vector<int>> &heights) {
        rows = heights.size();
        columns = heights[0].size();
        // 源点到各个点的体力值，记录的是这条路上相邻格子高度差绝对值的最大值
        vector<vector<int>> distance(rows, vector<int>(columns, INT_MAX));
        // 标记是否从堆中弹出过
        vector<vector<bool>> visited(rows, vector<bool>(columns, false));
        // (x, y, 体力值)，根据体力值排序
        priority_queue<vector<int>, vector<vector<int>>, cmp> heap;

        // 源点入堆
        heap.emplace(vector<int>{0, 0, 0});
        distance[0][0] = 0;

        while (!heap.empty()) {
            auto t = heap.top();
            heap.pop();
            int x = t[0];
            int y = t[1];
            int cost = t[2];
            if (x == rows - 1 && y == columns - 1) return cost;
            if (visited[x][y]) continue;
            visited[x][y] = true;

            for (int i = 0; i < 4; ++i) {
                int nx = x + move[i];
                int ny = y + move[i + 1];
                // 非法或者已经从堆弹出过，就忽略
                if (!isCoordinateLegal(nx, ny) || visited[nx][ny]) continue;
                // 相邻高度差的绝对值
                int gap = abs(heights[nx][ny] - heights[x][y]);
                // 这条路径到点 [nx, ny] 的体力值
                // 以前的代价是路径长度，这题的代价是这条路上相邻格子高度差绝对值的最大值
                int newCost = max(cost, gap);
                // 代价可以变小，就更新
                if (newCost < distance[nx][ny]) {
                    distance[nx][ny] = newCost;
                    heap.emplace(vector<int>{nx, ny, newCost});
                }
            }
        }
        return -1;
    }
};
```

### [778. 水位上升的泳池中游泳](https://leetcode.cn/problems/swim-in-rising-water/)

```c++
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

class Solution {
public:
    struct cmp {
        bool operator()(vector<int> &v1, vector<int> &v2) {
            return v1[2] > v2[2];
        }
    };

    vector<int> move{-1, 0, 1, 0, -1};
    int rows, columns;

    bool isCoordinateLegal(int row, int column) {
        return row >= 0 && row < rows && column >= 0 && column < columns;
    }

    int swimInWater(vector<vector<int>> &grid) {
        rows = grid.size();
        columns = grid[0].size();

        // 源点到各个点的最小游泳时间
        vector<vector<int>> distance(rows, vector<int>(columns, INT_MAX));
        // 标记是否从堆中弹出过
        vector<vector<bool>> visited(rows, vector<bool>(columns, false));
        // (x, y, 最小游泳时间)，根据最小游泳时间排序
        priority_queue<vector<int>, vector<vector<int>>, cmp> heap;

        // 至少要等到时间 grid[0][0]
        distance[0][0] = grid[0][0];
        heap.emplace(vector<int>{0, 0, grid[0][0]});

        while (!heap.empty()) {
            auto t = heap.top();
            heap.pop();
            int x = t[0];
            int y = t[1];
            int cost = t[2];
            if (x == rows - 1 && y == columns - 1) return cost;
            if (visited[x][y]) continue;
            visited[x][y] = true;

            for (int i = 0; i < 4; ++i) {
                int nx = x + move[i];
                int ny = y + move[i + 1];
                // 非法或者已经从堆弹出过，就忽略
                if (!isCoordinateLegal(nx, ny) || visited[nx][ny]) continue;
                // 新的代价是游到附近所要等待的最大时间
                int newCost = max(cost, grid[nx][ny]);
                // 代价可以变小，就更新
                if (newCost < distance[nx][ny]) {
                    distance[nx][ny] = newCost;
                    heap.emplace(vector<int>{nx, ny, newCost});
                }
            }
        }
        return -1;
    }
};
```

