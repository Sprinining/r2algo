#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define MAXN 100005
#define MAXM 200005
#define INF_MAX 0x3f3f3f3f

int head[MAXN];
int to[MAXM];
int next[MAXM];
int edge_cnt;
int weight[MAXM];

typedef struct {
    int index;     // 节点的编号
    int distance;  // 当前从源点到该节点的已知最短距离（作为堆排序的依据）
} Vertex;

// 静态内存池
Vertex vertices[MAXN];

// 小根堆，堆中元素数量最多就是节点个数
Vertex* heap[MAXN];
int heap_sz;
// 反向索引表
// -1：没有入堆，-2：已经出堆，>=0：在堆中的下标
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

void percolate_up(int top, int idx) {
    Vertex* v = heap[idx];
    int cur = idx;
    int parent = (cur - 1) >> 1;
    while (cur > top && heap[parent]->distance > v->distance) {
        heap[cur] = heap[parent];
        pos[heap[cur]->index] = cur;
        cur = parent;
        parent = (cur - 1) >> 1;
    }
    heap[cur] = v;
    pos[v->index] = cur;
}

void heapify(int idx) {
    Vertex* v = heap[idx];
    int cur = idx;
    int lc = (cur << 1) + 1;
    while (lc < heap_sz) {
        if (lc + 1 < heap_sz && heap[lc + 1]->distance < heap[lc]->distance)
            ++lc;
        heap[cur] = heap[lc];
        pos[heap[cur]->index] = cur;
        cur = lc;
        lc = (cur << 1) + 1;
    }
    heap[cur] = v;
    pos[v->index] = cur;
    percolate_up(idx, cur);
}

void push(Vertex* u) {
    heap[heap_sz++] = u;
    pos[u->index] = heap_sz - 1;
    percolate_up(0, heap_sz - 1);
}

Vertex* pop() {
    Vertex* res = heap[0];
    // 同步反向索引
    pos[res->index] = -2;
    if (--heap_sz > 0) {
        heap[0] = heap[heap_sz];
        pos[heap[0]->index] = 0;
        heapify(0);
    }
    return res;
}

int main() {
    int n, m, s;
    scanf("%d%d%d", &n, &m, &s);

    init_graph();
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        // 有向边建图
        add_edge(u, v, w);
    }

    // 初始都没有入堆
    memset(pos, -1, sizeof(pos));
    for (int i = 1; i <= n; ++i) {
        vertices[i].index = i;
        vertices[i].distance = INF_MAX;
    }

    heap_sz = 0;
    // 源点入堆
    vertices[s].distance = 0;
    push(&vertices[s]);

    while (heap_sz > 0) {
        int u = pop()->index;

        for (int e = head[u]; e > 0; e = next[e]) {
            int v = to[e];
            int w = weight[e];

            if (pos[v] == -2) {
                // 邻居 v 已经出堆
                continue;
            } else if (pos[v] == -1) {
                // 第一次入堆
                vertices[v].distance = vertices[u].distance + w;
                push(&vertices[v]);
            } else if (pos[v] >= 0) {
                // 松弛
                if (vertices[v].distance > vertices[u].distance + w) {
                    vertices[v].distance = vertices[u].distance + w;
                    // 根据反向索引表直接定位堆中位置
                    // 由于最短距离变小，所以需要上浮
                    percolate_up(0, pos[v]);
                }
            }
        }
    }

    for (int i = 1; i <= n; ++i) printf("%d ", vertices[i].distance);

    return 0;
}
