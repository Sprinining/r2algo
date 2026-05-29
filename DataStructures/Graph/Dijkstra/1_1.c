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

// 小根堆
Vertex heap[MAXM];
int heap_sz;
// dist[i] 表示源点到节点 i 的真实最短距离
int dist[MAXN];
// visit[i] 为 true 表示节点 i 已出堆结算，找到了确定最短路
bool visit[MAXN];

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
    Vertex v = heap[idx];
    int cur = idx;
    int parent = (cur - 1) >> 1;
    while (cur > top && heap[parent].distance > v.distance) {
        heap[cur] = heap[parent];
        cur = parent;
        parent = (cur - 1) >> 1;
    }
    heap[cur] = v;
}

void heapify(int idx) {
    Vertex v = heap[idx];
    int cur = idx;
    int lc = (cur << 1) + 1;
    while (lc < heap_sz) {
        if (lc + 1 < heap_sz && heap[lc + 1].distance < heap[lc].distance) ++lc;
        heap[cur] = heap[lc];
        cur = lc;
        lc = (cur << 1) + 1;
    }
    heap[cur] = v;
    percolate_up(idx, cur);
}

void push(Vertex v) {
    heap[heap_sz++] = v;
    percolate_up(0, heap_sz - 1);
}

Vertex pop() {
    Vertex res = heap[0];
    if (--heap_sz > 0) {
        heap[0] = heap[heap_sz];
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

    memset(visit, 0, sizeof(visit));
    // 初始化 dist 数组为无穷大
    memset(dist, 0x3f, sizeof(dist));

    // 源点初始化并首先入堆
    Vertex origin;
    origin.index = s;
    origin.distance = 0;
    push(origin);
    // 源点到自身距离在入堆时直接明确为 0
    dist[s] = 0;

    while (heap_sz > 0) {
        // 弹出当前已知未结算节点中距离源点最近的节点
        int u = pop().index;
        // 如果该点已经出过堆，说明之前弹出的那个值才是最短路
        // 堆里的这个是由于被多次松弛产生的“过时垃圾数据”，直接抛弃
        if (visit[u]) continue;
        visit[u] = true;

        // 遍历从 u 出发的所有邻接边 e
        for (int e = head[u]; e > 0; e = next[e]) {
            int v = to[e];
            int w = weight[e];
            // 松弛：如果终点 v 没结算，且经过 u 走到 v 的路径更短
            if (!visit[v] && dist[v] > dist[u] + w) {
                // 剪枝：入堆时就地更新 dist[v] 锁定门槛，防止堆膨胀
                dist[v] = dist[u] + w;
                Vertex node;
                node.index = v;
                node.distance = dist[v];
                push(node);
            }
        }
    }

    for (int i = 1; i <= n; ++i) printf("%d ", dist[i]);

    return 0;
}
