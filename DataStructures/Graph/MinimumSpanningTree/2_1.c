#include <endian.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAXN 100005
#define MAXQ 100005

// 顶点编号从 0 开始
int father[MAXN];

// queries 的索引数组
// 排序的时候不修改原始的数组，只修改索引数组
// 这样就不会丢失 queries 的顺序
int idxs[MAXQ];
int** questions;

void init(int n) {
    for (int i = 0; i < n; ++i) father[i] = i;
}

int find(int x) {
    if (father[x] == x) return x;
    return father[x] = find(father[x]);
}

bool is_same_set(int a, int b) { return find(a) == find(b); }

void unite(int a, int b) {
    int ra = find(a);
    int rb = find(b);
    if (ra == rb) return;
    father[rb] = ra;
}

int cmp_edge(const void* a, const void* b) {
    int* x = *(int**)a;
    int* y = *(int**)b;
    if (x[2] > y[2]) return 1;
    if (x[2] < y[2]) return -1;
    return 0;
}

int cmp_limit(const void* a, const void* b) {
    // 得到在 queries 中的下标
    int i = *(int*)a;
    int j = *(int*)b;
    // 比较 limit
    if (questions[i][2] > questions[j][2]) return 1;
    if (questions[i][2] < questions[j][2]) return -1;
    return 0;
}

bool* distanceLimitedPathsExist(int n, int** edgeList, int edgeListSize,
                                int* edgeListColSize, int** queries,
                                int queriesSize, int* queriesColSize,
                                int* returnSize) {
    questions = queries;
    init(n);
    // 根据边的权重升序排序
    qsort(edgeList, edgeListSize, sizeof(edgeList[0]), cmp_edge);

    // 初始化索引数组
    for (int i = 0; i < queriesSize; ++i) idxs[i] = i;
    // 根据 limit 升序排序，但只对索引数组修改
    qsort(idxs, queriesSize, sizeof(idxs[0]), cmp_limit);

    bool* res = malloc(sizeof(bool) * queriesSize);
    *returnSize = queriesSize;

    for (int i = 0, e_idx = 0; i < queriesSize; ++i) {
        // 处理的是第 q_idx 个原始提问
        int q_idx = idxs[i];
        int limit = queries[q_idx][2];
        int p = queries[q_idx][0];
        int q = queries[q_idx][1];

        // 严格小于 limit 的才能尝试进入 MST
        while (e_idx < edgeListSize && edgeList[e_idx][2] < limit) {
            unite(edgeList[e_idx][0], edgeList[e_idx][1]);
            ++e_idx;
        }

        res[q_idx] = is_same_set(p, q);
    }

    return res;
}
