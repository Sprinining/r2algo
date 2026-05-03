#include <string.h>

#define MAX_N 1001
#define MAX_E 2001
#define MMIN(a, b) ((a) > (b) ? (b) : (a))
#define MMAX(a, b) ((a) > (b) ? (a) : (b))
#define MMMAX(a, b, c) MMAX(MMAX(a, b), c)
#define MMMIN(a, b, c) MMIN(MMIN(a, b), c)

int head[MAX_N];
int next[MAX_E];
int to[MAX_E];
int edge_cnt;

// dfn 序号从 0 开始
int dfn_cnt;
int dfn[MAX_N];
// 子树的结点数
int sz[MAX_N];
// xorsum[i] = 以原始编号 i 的结点为根节点的子树的所有结点值的异或和
int xorsum[MAX_N];
int* nums;

void addEdge(int u, int v) {
    ++edge_cnt;
    next[edge_cnt] = head[u];
    to[edge_cnt] = v;
    head[u] = edge_cnt;
}

// 根据原始结点编号生成 dfn 序
void generateDFN(int u, int p) {
    if (head[u] == 0) return;
    // 记录 dfn 序号
    int dfn_idx = dfn_cnt++;
    dfn[u] = dfn_idx;
    sz[u] = 1;
    // 记录异或和
    xorsum[u] = nums[u];
    for (int e = head[u]; e > 0; e = next[e]) {
        int v = to[e];
        // 跳过父结点
        if (v == p) continue;
        generateDFN(v, u);
        // 加上子树结点数
        sz[u] += sz[v];
        // 异或上子树
        xorsum[u] ^= xorsum[v];
    }
}

void buildGraph(int** edges, int n) {
    edge_cnt = 0;
    memset(head, 0, sizeof(*head) * MAX_N);

    // 根据结点原始编号建图
    for (int i = 0; i < n; ++i) {
        addEdge(edges[i][0], edges[i][1]);
        addEdge(edges[i][1], edges[i][0]);
    }
}

void buildDFN() {
    dfn_cnt = 0;
    // 把原始编号为 0 的结点当作根节点
    generateDFN(0, 0);
}

int res;
void compute(int u1, int v1, int u2, int v2) {
    // dfn 更小的才是子树的根
    int r1 = dfn[u1] > dfn[v1] ? u1 : v1;
    int r2 = dfn[u2] > dfn[v2] ? u2 : v2;
    // dfn 较小的一个为 r1
    if (dfn[r1] > dfn[r2]) {
        int t = r1;
        r1 = r2;
        r2 = t;
    }

    int x1, x2;
    if (dfn[r2] <= dfn[r1] + sz[r1] - 1) {
        // r2 是 r1 后代
        x2 = xorsum[r2];
        x1 = xorsum[r1] ^ xorsum[r2];
    } else {
        // 并列关系
        x1 = xorsum[r1];
        x2 = xorsum[r2];
    }
    int x3 = xorsum[0] ^ x1 ^ x2;
    int cur = MMMAX(x1, x2, x3) - MMMIN(x1, x2, x3);
    res = MMIN(res, cur);
}

int minimumScore(int* _nums, int numsSize, int** edges, int edgesSize, int* edgesColSize) {
    nums = _nums;
    res = 0x7fffffff;
    buildGraph(edges, edgesSize);
    buildDFN();

    for (int i = 0; i < edgesSize; ++i) {
        for (int j = i + 1; j < edgesSize; ++j) {
            compute(edges[i][0], edges[i][1], edges[j][0], edges[j][1]);
        }
    }
    return res;
}
