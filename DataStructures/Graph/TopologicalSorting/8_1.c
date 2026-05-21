#include <endian.h>
#include <string.h>

#define MAXN 50005
#define MAXE 50005
#define MMAX(a, b) ((a) > (b) ? (a) : (b))

int head[MAXN];
int to[MAXE];
int next[MAXE];
int edge_cnt;
// 课程编号从 0 开始
int indegree[MAXN];
int queue[MAXN];
int l, r;
// cost[i] = 课程 i 学完所需要的最多月份
int cost[MAXN];

void init_graph() {
    edge_cnt = 1;
    memset(head, 0, sizeof(head));
    memset(indegree, 0, sizeof(indegree));
    l = 0;
    r = 0;
    memset(cost, 0, sizeof(cost));
}

void add_edge(int u, int v) {
    int edge_idx = edge_cnt++;
    next[edge_idx] = head[u];
    to[edge_idx] = v;
    head[u] = edge_idx;
    ++indegree[v];
}

int minimumTime(int n, int** relations, int relationsSize,
                int* relationsColSize, int* time, int timeSize) {
    init_graph();
    // 编号改为从 0 开始
    for (int i = 0; i < relationsSize; ++i)
        add_edge(relations[i][0] - 1, relations[i][1] - 1);

    for (int i = 0; i < n; ++i)
        if (indegree[i] == 0) queue[r++] = i;

    int res = 0;
    while (l < r) {
        int u = queue[l++];
        // 结算 u: 加上自身耗时
        cost[u] += time[u];
        res = MMAX(res, cost[u]);
        for (int e = head[u]; e > 0; e = next[e]) {
            int v = to[e];
            // v 尚未结算的时候，cost[v] 表示到达 v 的最长时间
            cost[v] = MMAX(cost[v], cost[u]);
            if (--indegree[v] == 0) queue[r++] = v;
        }
    }

    return res;
}
