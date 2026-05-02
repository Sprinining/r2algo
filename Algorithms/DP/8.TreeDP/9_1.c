#include <string.h>

#define MMAX(a, b) ((a) > (b) ? (a) : (b))
#define MAX_NODE_CNT 100001
#define MAX_EDGE_CNT 200001

int head[MAX_NODE_CNT];
int next[MAX_EDGE_CNT];
int to[MAX_EDGE_CNT];
int e_idx;

int maxLen;
char* s;

void initGraph() {
    e_idx = 1;
    memset(head, 0, sizeof(*head) * MAX_NODE_CNT);
}

void addEdge(int u, int v) {
    next[e_idx] = head[u];
    to[e_idx] = v;
    head[u] = e_idx++;
}

// 返回必须以当前结点为端点的最长路径
int dfs(int u, int p) {
    if (head[u] == 0) return 0;
    // 必须以当前结点为端点的最长路径和次长路径，不包含自身
    int m1 = 0, m2 = 0;
    for (int e = head[u]; e > 0; e = next[e]) {
        int v = to[e];
        // 避免无限递归
        if (v == p) continue;
        int c = dfs(v, u);
        // 不能是相同字符
        if (s[u] == s[v]) continue;
        if (c >= m1) {
            m2 = m1;
            m1 = c;
        } else if (c < m1 && c > m2) {
            m2 = c;
        }
    }
    maxLen = MMAX(maxLen, m1 + m2 + 1);
    return m1 + 1;
}

int longestPath(int* parent, int parentSize, char* _s) {
    if (parentSize == 1) return 1;
    maxLen = 0;
    s = _s;
    initGraph();
    // 跳过根节点
    for (int i = 1; i < parentSize; ++i) {
        addEdge(parent[i], i);
        addEdge(i, parent[i]);
    }
    dfs(0, 0);
    return maxLen;
}
