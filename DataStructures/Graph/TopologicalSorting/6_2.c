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

int indegree[MAXN];
// 源点到 i 号节点的路径总数
int path[MAXN];
// 静态数组模拟队列
int q[MAXN];
// 队列的左右指针
int l = 0, r = 0;

void init_graph() {
    edge_cnt = 1;
    memset(head, 0, sizeof(head));
    memset(indegree, 0, sizeof(indegree));
    memset(path, 0, sizeof(path));
}

void add_edge(int u, int v) {
    int edge_idx = edge_cnt++;
    next[edge_idx] = head[u];
    to[edge_idx] = v;
    head[u] = edge_idx;
    ++indegree[v];
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

    // 将所有入度为 0 的源点入队，并初始化路径数为 1
    for (int i = 1; i <= n; ++i) {
        if (indegree[i] == 0) {
            q[r++] = i;
            path[i] = 1;
        }
    }

    int res = 0;
    while (l < r) {
        int u = q[l++];  // 出队
        if (head[u] == 0) {
            // head[u] == 0 说明没有后继边，即为汇点
            res = ((ll)res + path[u]) % MOD;
        } else {
            for (int e = head[u]; e > 0; e = next[e]) {
                int v = to[e];
                // 路径总数向后传递
                path[v] = ((ll)path[v] + path[u]) % MOD;
                if (--indegree[v] == 0) q[r++] = v;
            }
        }
    }

    printf("%d\n", res);
    return 0;
}
