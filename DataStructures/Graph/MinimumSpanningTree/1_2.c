#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define MAXN 5005
#define MAXM 400005

int head[MAXN];
int to[MAXM];
int next[MAXM];
int edge_cnt;
int weight[MAXM];

// 标记顶点是否已经加入 MST
bool visit[MAXN];

// heap[i][0] 表示这条边去往的顶点 v
// heap[i][1] 是边的权重，根据权重构建小根堆
// 编号从 0 开始
int heap[MAXM][2];
int heap_sz;

void init_heap() { heap_sz = 0; }

void percolate(int top, int idx) {
    int v = heap[idx][0];
    int w = heap[idx][1];
    int cur = idx;
    int parent = (cur - 1) >> 1;
    while (cur > top && heap[parent][1] > w) {
        heap[cur][0] = heap[parent][0];
        heap[cur][1] = heap[parent][1];
        cur = parent;
        parent = (cur - 1) >> 1;
    }
    heap[cur][0] = v;
    heap[cur][1] = w;
}

void heapify(int idx) {
    int v = heap[idx][0];
    int w = heap[idx][1];
    int cur = idx;
    int lc = (cur << 1) + 1;
    while (lc < heap_sz) {
        if (lc + 1 < heap_sz && heap[lc + 1][1] < heap[lc][1]) ++lc;
        heap[cur][0] = heap[lc][0];
        heap[cur][1] = heap[lc][1];
        cur = lc;
        lc = (cur << 1) + 1;
    }

    heap[cur][0] = v;
    heap[cur][1] = w;

    percolate(idx, cur);
}

void push(int v, int w) {
    int heap_idx = heap_sz++;
    heap[heap_idx][0] = v;
    heap[heap_idx][1] = w;
    percolate(0, heap_idx);
}

void pop(int* v, int* w) {
    *v = heap[0][0];
    *w = heap[0][1];
    heap[0][0] = heap[heap_sz - 1][0];
    heap[0][1] = heap[heap_sz - 1][1];
    --heap_sz;
    heapify(0);
}

void init_graph(int n) {
    edge_cnt = 1;
    memset(head, 0, sizeof(int) * (n + 1));
    memset(visit, 0, sizeof(bool) * (n + 1));
}

void add_edge(int u, int v, int w) {
    int edge_idx = edge_cnt++;
    next[edge_idx] = head[u];
    to[edge_idx] = v;
    head[u] = edge_idx;
    // 记录权重
    weight[edge_idx] = w;
}

int main() {
    int n, m;
    scanf("%d%d", &n, &m);

    init_graph(n);
    init_heap();

    for (int i = 0; i < m; ++i) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        // 无向图
        add_edge(u, v, w);
        add_edge(v, u, w);
    }

    int res = 0;
    int cnt = 0;
    // 随便找一个点作为起始点
    visit[1] = true;
    ++cnt;
    // 邻接边入堆
    for (int e = head[1]; e > 0; e = next[e]) push(to[e], weight[e]);

    while (heap_sz > 0 && cnt < n) {
        int v, w;
        // 弹出权重最小的边
        pop(&v, &w);
        // v 已经在 MST 中
        if (visit[v]) continue;
        visit[v] = true;
        res += w;
        ++cnt;
        // 剪枝：没在 MST 中的才能入堆
        // 能提前排除的就排除，不要进堆浪费时间
        for (int e = head[v]; e > 0; e = next[e])
            if (!visit[to[e]]) push(to[e], weight[e]);
    }

    if (cnt == n) {
        printf("%d\n", res);
    } else {
        printf("orz\n");
    }

    return 0;
}
