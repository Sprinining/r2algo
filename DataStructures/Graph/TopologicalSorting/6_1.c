#include <stdio.h>
#include <string.h>

#define MOD 80112002
#define MAXN 5005
#define MAXM 500005

typedef long long ll;

int head[MAXN];
int to[MAXM];
int next[MAXM];
int edge_cnt;
// 节点编号从 1 开始
int indegree[MAXN];
int dp[MAXN];

void init_graph() {
    edge_cnt = 1;
    memset(head, 0, sizeof(head));
    memset(indegree, 0, sizeof(indegree));
    memset(dp, -1, sizeof(dp));
}

void add_edge(int u, int v) {
    int edge_idx = edge_cnt++;
    next[edge_idx] = head[u];
    to[edge_idx] = v;
    head[u] = edge_idx;
    ++indegree[v];
}

// 从 idx 节点开始，到汇点的路径数
int dfs(int u) {
    if (head[u] == 0) return 1;
    if (dp[u] != -1) return dp[u];
    int res = 0;
    for (int e = head[u]; e > 0; e = next[e])
        res = ((ll)res + dfs(to[e])) % MOD;
    return dp[u] = res;
}

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    init_graph();
    for (int i = 0; i < m; ++i) {
        int u, v;
        scanf("%d%d", &u, &v);
        add_edge(u, v);
    }

    // 源点到汇点的路径总数
    int res = 0;
    for (int i = 1; i <= n; ++i) {
        if (indegree[i] != 0) continue;
        res = ((ll)res + dfs(i)) % MOD;
    }

    printf("%d\n", res);
    return 0;
}
