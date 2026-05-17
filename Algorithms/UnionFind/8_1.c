#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 300

int father[MAXN];
int sz[MAXN];
// 集合的病毒源头，-1 表示没有病毒，-2 表示有多个病毒源头
int source[MAXN];
// 是否是病毒
bool virus[MAXN];
// 删掉节点能拯救的节点个数
int save[MAXN];

int cmp(const void* a, const void* b) {
    int x = *((int*)a);
    int y = *((int*)b);
    if (x > y) return 1;
    if (x < y) return -1;
    return 0;
}

void build(int n) {
    for (int i = 0; i < n; ++i) {
        father[i] = i;
        sz[i] = 1;
        source[i] = -1;
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
    if (sz[ra] < sz[rb]) {
        father[ra] = rb;
        sz[rb] += sz[ra];
    } else {
        father[rb] = ra;
        sz[ra] += sz[rb];
    }
}

int minMalwareSpread(int** graph, int graphSize, int* graphColSize,
                     int* initial, int initialSize) {
    int n = graphSize;
    // 根据病毒下标升序排序
    qsort(initial, initialSize, sizeof(*initial), cmp);
    build(n);

    memset(virus, 0, sizeof(virus));
    for (int i = 0; i < initialSize; ++i) virus[initial[i]] = true;

    // 没有病毒的联通节点作为一个集合
    for (int i = 0; i < n; ++i) {
        // 其中有个是病毒
        if (virus[i]) continue;
        for (int j = i + 1; j < n; ++j) {
            // 不相连，或是病毒
            if (graph[i][j] == 0 || virus[j]) continue;
            unite(i, j);
        }
    }

    // 给上面得到的所有集合记录病毒源头
    for (int i = 0; i < initialSize; ++i) {
        int v = initial[i];
        for (int j = 0; j < n; ++j) {
            // 如果不相连就跳过
            // 给与病毒相连的正常集合记录，如果相连的也是病毒也跳过
            if (graph[v][j] == 0 || virus[j]) continue;
            // 找到集合代表元
            int rj = find(j);
            if (source[rj] == -1) {
                source[rj] = v;
            } else if (source[rj] != -2 && source[rj] != v) {
                // 已经有病毒源头，且又出现个新的病毒源头
                // -2 表示有多个病毒源头
                source[rj] = -2;
            }
        }
    }

    memset(save, 0, sizeof(save));
    // 是集合代表元且集合的病毒源头有且仅有一个
    for (int i = 0; i < n; ++i)
        if (father[i] == i && source[i] >= 0) save[source[i]] += sz[find(i)];

    // 判断哪个病毒拯救的最多
    int res = initial[0];
    for (int i = 1; i < initialSize; ++i)
        if (save[initial[i]] > save[res]) res = initial[i];

    return res;
}
