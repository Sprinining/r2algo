#include <stdlib.h>
#include <string.h>

#define MAXN 502
#define MAXE ((MAXN * (MAXN - 1)) / 2)

int head[MAXN];
int to[MAXE];
int next[MAXE];
int edge_cnt;
int indegree[MAXN];
int queue[MAXN];
int l, r;

void init_graph() {
    edge_cnt = 1;
    memset(head, 0, sizeof(head));
    memset(indegree, 0, sizeof(indegree));
    l = 0;
    r = 0;
}

void add_edge(int u, int v) {
    int edge_idx = edge_cnt++;
    next[edge_idx] = head[u];
    to[edge_idx] = v;
    head[u] = edge_idx;
    ++indegree[v];
}

int* loudAndRich(int** richer, int richerSize, int* richerColSize, int* quiet,
                 int quietSize, int* returnSize) {
    int n = quietSize;
    int m = richerSize;
    init_graph();
    for (int i = 0; i < m; ++i) add_edge(richer[i][0], richer[i][1]);

    for (int i = 0; i < n; ++i)
        if (indegree[i] == 0) queue[r++] = i;

    int* res = malloc(sizeof(int) * n);
    // 初始是自己
    for (int i = 0; i < n; ++i) res[i] = i;
    *returnSize = n;
    while (l < r) {
        int u = queue[l++];
        for (int e = head[u]; e > 0; e = next[e]) {
            int v = to[e];
            if (quiet[res[u]] < quiet[res[v]]) res[v] = res[u];
            if (--indegree[v] == 0) queue[r++] = v;
        }
    }

    return res;
}
