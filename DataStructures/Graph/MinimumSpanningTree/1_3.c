#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define MAXN 5005
#define MAXM 400005

// 链式前向星存图
int head[MAXN];
int to[MAXM];
int next[MAXM];
int weight[MAXM];
int edge_cnt;

// heap[i] = u：堆中第 i 个位置存放的是顶点编号 u (heap 下标从 0 开始)
int heap[MAXN];
int heap_sz;

// dist[u] = d：顶点 u 到当前 MST 集合的最短距离 (dist 下标从 1 开始)
// 整个小顶堆的大小比较严格基于 dist[heap[i]] 的值
int dist[MAXN];

// pos[u] = i：反向索引表。顶点 u 当前在 heap 数组中的下标是 i
// 状态约定：
// -1 ：尚未进入堆中（初始状态）
// -2 ：已经加入了 MST 集合（已出堆）
// >=0：顶点在堆中的具体下标
int pos[MAXN];

void init_heap() {
    heap_sz = 0;
    memset(pos, -1, sizeof(pos));
}

void percolate_up(int top, int idx) {
    int v = heap[idx];
    int d = dist[v];
    int cur = idx;
    int parent = (cur - 1) >> 1;

    while (cur > top && dist[heap[parent]] > d) {
        heap[cur] = heap[parent];
        // 同步更新反向索引表
        pos[heap[cur]] = cur;
        cur = parent;
        parent = (cur - 1) >> 1;
    }

    heap[cur] = v;
    pos[v] = cur;
}

void heapify(int idx) {
    int v = heap[idx];
    int cur = idx;
    int lc = (cur << 1) + 1;

    while (lc < heap_sz) {
        if (lc + 1 < heap_sz && dist[heap[lc + 1]] < dist[heap[lc]]) ++lc;
        heap[cur] = heap[lc];
        pos[heap[cur]] = cur;
        cur = lc;
        lc = (cur << 1) + 1;
    }
    heap[cur] = v;
    pos[v] = cur;
    percolate_up(idx, cur);
}

void push(int v) {
    int heap_idx = heap_sz++;
    heap[heap_idx] = v;
    pos[v] = heap_idx;
    percolate_up(0, heap_idx);
}

int pop() {
    int u = heap[0];
    // 只要出堆，立刻打上 -2 标签，代表正式委任进 MST 集合
    pos[u] = -2;
    --heap_sz;
    if (heap_sz > 0) {
        heap[0] = heap[heap_sz];
        pos[heap[0]] = 0;
        heapify(0);
    }
    return u;
}

void init_graph(int n) {
    edge_cnt = 1;
    memset(head, 0, sizeof(int) * (n + 1));
}

void add_edge(int u, int v, int w) {
    int edge_idx = edge_cnt++;
    next[edge_idx] = head[u];
    to[edge_idx] = v;
    weight[edge_idx] = w;
    head[u] = edge_idx;
}

int main() {
    int n, m;
    if (scanf("%d%d", &n, &m) != 2) return 0;

    init_graph(n);
    init_heap();

    for (int i = 0; i < m; ++i) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        add_edge(u, v, w);
        add_edge(v, u, w);
    }

    int res = 0;
    int cnt = 0;
    // 任意挑选 1 号节点作为树的根节点，将其距离设为 0 并推入堆
    dist[1] = 0;
    push(1);

    while (heap_sz > 0 && cnt < n) {
        // 弹出当前距离 MST 集合最近的顶点 v
        int v = pop();
        res += dist[v];
        ++cnt;

        // 考察从 v 出发的每一条邻接边
        for (int e = head[v]; e > 0; e = next[e]) {
            int vv = to[e];
            if (pos[vv] == -2) {
                // P1：vv 已经加入 MST 集合
                continue;
            } else if (pos[vv] == -1) {
                // P2：vv 首次被发现，从未进过堆
                dist[vv] = weight[e];
                push(vv);
            } else if (pos[vv] >= 0) {
                // P3：vv 目前已经在堆里
                // 如果这次发现的新边权重，比它之前记录的旧距离还要短
                if (weight[e] < dist[vv]) {
                    dist[vv] = weight[e];  // 改写更优的距离值
                    // 索引堆：利用 pos[vv] 以 O(1) 复杂度得到该点在堆中的下标
                    percolate_up(0, pos[vv]);
                }
            }
        }
    }

    // 判定是否能生成覆盖全图的树
    if (cnt == n) {
        printf("%d\n", res);
    } else {
        printf("orz\n");
    }

    return 0;
}
