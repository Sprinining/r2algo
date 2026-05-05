#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define IDX(i, j, k) ((i) * (J) * (K) + (j) * (K) + (k))
#define MAX_N 302
#define MAX_E 301
#define MMAX(a, b) ((a) > (b) ? (a) : (b))

int head[MAX_N];
int next[MAX_E];
int to[MAX_E];
// 记录直接孩子的个数
int child[MAX_N];
int edge_cnt;

int n, m;
int* father;
int* score;
int I, J, K;
int* dp;

void addEdge(int u, int v) {
    ++edge_cnt;
    next[edge_cnt] = head[u];
    to[edge_cnt] = v;
    head[u] = edge_cnt;
    ++child[u];
}

void buildGraph() {
    edge_cnt = 0;
    memset(head, 0, sizeof(*head) * MAX_N);
    memset(child, 0, sizeof(*child) * MAX_N);
    // 有向图
    for (int i = 1; i < n; ++i) addEdge(father[i], i);
}

// 在根节点 u 的前 cnt 个孩子里选 k 门课程能获得的最大得分
int dfs(int u, int cnt, int k) {
    if (k == 0) return 0;
    if (k == 1 || cnt == 0) return score[u];
    if (dp[IDX(u, cnt, k)] != -1) return dp[IDX(u, cnt, k)];

    // 找到第 cnt 个孩子结点编号
    int e = head[u];
    for (int i = 1; i < cnt; ++i) e = next[e];
    int v = to[e];

    // u 的前 cnt-1 个孩子用掉 s 个名额，最后一个孩子用 k-s-1 个名额
    int res = 0x80000000;
    for (int s = 0; s <= k - 1; ++s) {
        // int p1 = dfs(u, cnt - 1, s + 1) - score[u];
        // int p2 = dfs(v, child[v], k - 1 - s);
        // res = MMAX(res, p1 + p2 + score[u]);
        // u 的前 cnt-1 个孩子用 s 个名额，但是 u 自身要用一个，所以是 s+1
        res = MMAX(res, dfs(u, cnt - 1, s + 1) + dfs(v, child[v], k - 1 - s));
    }
    dp[IDX(u, cnt, k)] = res;
    return res;
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

    I = n;
    J = n;
    K = m + 1;
    dp = malloc(sizeof(*dp) * I * J * K);
    memset(dp, -1, sizeof(*dp) * I * J * K);

    printf("%d\n", dfs(0, child[0], m));
}
