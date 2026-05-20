#include <stdlib.h>
#include <string.h>

#define MAXN 2000
#define MAXE (MAXN * (MAXN - 1))

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

void init_graph(int** edges, int edge_size) {
    edge_cnt = 1;
    memset(head, 0, sizeof(head));
    memset(indegree, 0, sizeof(indegree));
    for (int i = 0; i < edge_size; ++i) add_edge(edges[i][1], edges[i][0]);
}

void init_stk(int n) {
    top = 0;
    // 记录初始入读为 0 的节点
    for (int u = 0; u < n; ++u)
        if (indegree[u] == 0) stk[top++] = u;
}

int* findOrder(int numCourses, int** prerequisites, int prerequisitesSize,
               int* prerequisitesColSize, int* returnSize) {
    init_graph(prerequisites, prerequisitesSize);
    init_stk(numCourses);

    int* res = malloc(sizeof(int) * numCourses);
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
    *returnSize = numCourses == len ? len : 0;
    return res;
}
