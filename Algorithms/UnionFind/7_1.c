#include <stdlib.h>

#define MMAX(a, b) ((a) > (b) ? (a) : (b))
#define MAXN 30000

int* vals;
int father[MAXN];
// 集合中元素最大值
int max_val[MAXN];
// 集合中最大值的个数
int cnt[MAXN];
int res;

void build(int n) {
    for (int i = 0; i < n; ++i) {
        father[i] = i;
        // 最大值就是自己
        max_val[i] = vals[i];
        cnt[i] = 1;
    }
}

int find(int x) {
    if (father[x] == x) return x;
    return father[x] = find(father[x]);
}

void unite(int a, int b) {
    int ra = find(a);
    int rb = find(b);
    if (ra == rb) return;
    // rb 挂到 ra 上
    father[rb] = ra;

    // 调整最大值和最大值的个数
    int ma = max_val[ra];
    int mb = max_val[rb];
    if (ma == mb) {
        // 累计答案
        res += cnt[ra] * cnt[rb];
        cnt[ra] += cnt[rb];
    } else if (ma < mb) {
        max_val[ra] = mb;
        cnt[ra] = cnt[rb];
    }
}

int cmp(const void* a, const void* b) {
    int* n1 = *((int**)a);
    int* n2 = *((int**)b);
    int m1 = MMAX(vals[n1[0]], vals[n1[1]]);
    int m2 = MMAX(vals[n2[0]], vals[n2[1]]);
    if (m1 > m2) return 1;
    if (m1 < m2) return -1;
    return 0;
}

int numberOfGoodPaths(int* _vals, int valsSize, int** edges, int edgesSize,
                      int* edgesColSize) {
    vals = _vals;
    // 根据边的两个端点的值的大小的较大者排序
    qsort(edges, edgesSize, sizeof(*edges), cmp);

    build(valsSize);

    // 单个节点也是合法的好路径
    res = valsSize;
    for (int i = 0; i < edgesSize; ++i) unite(edges[i][0], edges[i][1]);

    return res;
}
