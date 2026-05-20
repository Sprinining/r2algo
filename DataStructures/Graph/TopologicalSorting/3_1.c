#include <stdio.h>
#include <string.h>

#define MAXN 100001
#define MAXM 100001

int head[MAXN];
int to[MAXM];
int next[MAXM];
int edge_cnt;
// 顶点编号从 1 开始
int indegree[MAXN];

// 小根堆
int heap[MAXN];
int heap_sz;

void init_graph(int n) {
    // 边的编号从 1 开始
    edge_cnt = 1;
    memset(head, 0, sizeof(int) * n);
    memset(indegree, 0, sizeof(int) * n);
}

void add_edge(int u, int v) {
    int edge_idx = edge_cnt++;
    next[edge_idx] = head[u];
    to[edge_idx] = v;
    head[u] = edge_idx;
    ++indegree[v];
}

void percolate_up(int top, int idx) {
    int val = heap[idx];
    int cur = idx;
    int parent = (cur - 1) / 2;
    while (cur > top && heap[parent] > val) {
        heap[cur] = heap[parent];
        cur = parent;
        parent = (cur - 1) / 2;
    }
    heap[cur] = val;
}

void heapify(int idx) {
    int val = heap[idx];
    int cur = idx;
    int lc = 2 * cur + 1;
    while (lc < heap_sz) {
        if (lc + 1 < heap_sz && heap[lc + 1] < heap[lc]) ++lc;
        heap[cur] = heap[lc];
        cur = lc;
        lc = 2 * cur + 1;
    }
    heap[cur] = val;
    percolate_up(idx, cur);
}

int pop_heap() {
    int res = heap[0];
    heap[0] = heap[--heap_sz];
    heapify(0);
    return res;
}

void push_heap(int x) {
    heap[heap_sz++] = x;
    percolate_up(0, heap_sz - 1);
}

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    init_graph(n);
    for (int i = 0; i < m; ++i) {
        int u, v;
        scanf("%d%d", &u, &v);
        add_edge(u, v);
    }

    heap_sz = 0;
    for (int i = 1; i <= n; ++i)
        if (indegree[i] == 0) push_heap(i);

    while (heap_sz != 0) {
        int u = pop_heap();
        for (int e = head[u]; e > 0; e = next[e]) {
            int v = to[e];
            if (--indegree[v] == 0) push_heap(v);
        }
        printf("%d ", u);
    }

    return 0;
}
