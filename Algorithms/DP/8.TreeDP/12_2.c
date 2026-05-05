#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 302
#define MAX_E 301
#define MAX_M 301
#define MMAX(a, b) ((a) > (b) ? (a) : (b))

int head[MAX_N];
int next[MAX_E];
int to[MAX_E];
int edge_cnt;

int n, m;
int* father;
int* score;
int dp[MAX_N][MAX_M];

// 下标为 dfn 序号，从 0 开始，值为原始结点编号
int rdfn[MAX_N];
// 原始结点编号为下标，从 0 开始，值为子树结点总数
int sz[MAX_N];
int dfn_cnt;

void addEdge(int u, int v) {
    ++edge_cnt;
    next[edge_cnt] = head[u];
    to[edge_cnt] = v;
    head[u] = edge_cnt;
}

void buildGraph() {
    edge_cnt = 0;
    memset(head, 0, sizeof(*head) * MAX_N);
    // 有向图
    for (int i = 1; i < n; ++i) addEdge(father[i], i);
}

void dfs(int u) {
    rdfn[dfn_cnt++] = u;
    ++sz[u];
    for (int e = head[u]; e > 0; e = next[e]) {
        int v = to[e];
        dfs(v);
        sz[u] += sz[v];
    }
}

void generateDFN() {
    dfn_cnt = 0;
    memset(sz, 0, sizeof(*sz) * MAX_N);
    dfs(0);
}

int main() {
    scanf("%d%d", &n, &m);
    // 多加一个编号为 0 的虚拟头结点
    ++n;
    // 虚拟头结点必选
    ++m;
    father = malloc(sizeof(*father) * n);
    score = malloc(sizeof(*score) * n);
    father[0] = -1;
    score[0] = 0;
    for (int i = 1; i < n; ++i) scanf("%d%d", &father[i], &score[i]);

    buildGraph();
    generateDFN();

    // dfn 序号为 n 的初始情况
    memset(dp[n], 0, sizeof(*dp[n]) * (m + 1));
    // dfn 序号 0～n-1
    // 原始结点编号 0～n-1
    // 根据 dfn 序号逆序遍历，对当前的根节点进行如下操作
    // 选择的总节点数从 1 尝试到 m
    // p1: 不要当前节点
    // 那么当前节点及其子树，也就是 dfn 序号 i~i+sz[u]-1 范围的都不能选，因为不能连成一片
    // 只能从 dfn 序号 i+sz[u] 开始往后选 j 个节点，即 dp[i+sz[u]][j]
    // p2: 要当前节点
    // 剩下 j-1 个节点从 dfn 序号 i+1~n 范围内选，即 dp[i+1][j-1]，再加上当前值 score[u]
    // 这些节点在加了一个虚拟头节点的情况下，就能连成一片
    for (int i = n - 1; i >= 0; --i) {
        for (int j = 1; j <= m; ++j) {
            int u = rdfn[i];
            // dp[i][j] = dfn 序号 i~n 上选择 j 个
            dp[i][j] = MMAX(dp[i + sz[u]][j], score[u] + dp[i + 1][j - 1]);
        }
    }

    printf("%d\n", dp[0][m]);
}
