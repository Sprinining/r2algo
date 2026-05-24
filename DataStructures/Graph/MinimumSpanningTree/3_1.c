#include <stdio.h>
#include <string.h>

#define MAXN 305
#define MAXM 16005
#define MMAX(a, b) ((a) > (b) ? (a) : (b))

int head[MAXN];
int to[MAXM];
int next[MAXM];
int edge_cnt;
int weight[MAXM];

// 小根堆：里面存放节点编号
int heap[MAXN];
int heap_sz;

// 顶点编号从 1 开始
int dist[MAXN];
// 反向索引表
// -1：尚未进入堆，-2：已经进入 MST，>=0：在堆中的下标
int pos[MAXN];

void init_graph() {
    edge_cnt = 1;
    memset(head, 0, sizeof(head));
}

void add_edge(int u, int v, int w) {
    int edge_idx = edge_cnt++;
    next[edge_idx] = head[u];
    to[edge_idx] = v;
    head[u] = edge_idx;
    weight[edge_idx] = w;
}

void init_heap() {
    heap_sz = 0;
    memset(pos, -1, sizeof(pos));
}

void percolate_up(int top, int idx) {
    int v = heap[idx];
    int w = dist[v];
    int cur = idx;
    int parent = (cur - 1) >> 1;
    while (cur > top && dist[heap[parent]] > w) {
        heap[cur] = heap[parent];
        // 同步索引
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

void push(int u) {
    int heap_idx = heap_sz++;
    heap[heap_idx] = u;
    pos[u] = heap_idx;
    percolate_up(0, heap_idx);
}

int pop() {
    int res = heap[0];
    pos[res] = -2;
    --heap_sz;
    if (heap_sz > 0) {
        heap[0] = heap[heap_sz];
        pos[heap[0]] = 0;
        heapify(0);
    }
    return res;
}

int main() {
    int n, m;
    scanf("%d%d", &n, &m);

    init_graph();
    init_heap();

    for (int i = 0; i < m; ++i) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        add_edge(u, v, w);
        add_edge(v, u, w);
    }

    int max_w = -1;
    push(1);
    while (heap_sz > 0) {
        int v = pop();
        max_w = MMAX(max_w, dist[v]);
        for (int e = head[v]; e > 0; e = next[e]) {
            int vv = to[e];
            if (pos[vv] == -2) {
                continue;
            } else if (pos[vv] == -1) {
                dist[vv] = weight[e];
                push(vv);
            } else {
                if (weight[e] < dist[vv]) {
                    // 快速定位 vv 在堆中的位置
                    dist[vv] = weight[e];
                    percolate_up(0, pos[vv]);
                }
            }
        }
    }

    printf("%d %d\n", n - 1, max_w);

    return 0;
}
