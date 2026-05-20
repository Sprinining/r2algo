#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 200001
#define MAXE 200001

int head[MAXN];
int to[MAXE];
int next[MAXE];
int edge_cnt;
int indegree[MAXN];
// 记录入度为 0 的尚未输出的节点编号
// 用栈还是队列无所谓，只是会影响输出顺序
int stk[MAXN];
int top;

// 有向边 u->v
void add_edge(int u, int v) {
    int edge_idx = edge_cnt++;
    next[edge_idx] = head[u];
    to[edge_idx] = v;
    head[u] = edge_idx;
    ++indegree[v];
}

void init_graph() {
    edge_cnt = 1;
    memset(head, 0, sizeof(head));
    memset(indegree, 0, sizeof(indegree));
}

void init_stk(int n) {
    top = 0;
    // 记录初始入读为 0 的节点
    // 顶点编号从 1 开始
    for (int u = 1; u <= n; ++u)
        if (indegree[u] == 0) stk[top++] = u;
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
    init_stk(n);

    int* res = malloc(sizeof(int) * n);
    int len = 0;
    // 栈不空
    while (top != 0) {
        int u = stk[--top];
        // 断开 u->v
        for (int e = head[u]; e > 0; e = next[e]) {
            int v = to[e];
            if (--indegree[v] == 0) stk[top++] = v;
        }
        res[len++] = u;
    }

    if (len != n) {
        printf("-1\n");
    } else {
        for (int i = 0; i < len - 1; ++i) printf("%d ", res[i]);
        printf("%d", res[len - 1]);
    }
    return 0;
}
