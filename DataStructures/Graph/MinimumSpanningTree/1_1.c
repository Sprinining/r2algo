#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define MAXN 5005
#define MAXM 200005

int edge[MAXM][3];
int father[MAXN];

int cmp(const void* a, const void* b) {
    int* x = (int*)a;
    int* y = (int*)b;
    if (x[2] > y[2]) return 1;
    if (x[2] < y[2]) return -1;
    return 0;
}

void init(int n) {
    // 顶点编号从 1 开始
    for (int i = 1; i <= n; ++i) father[i] = i;
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

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; ++i)
        scanf("%d%d%d", &edge[i][0], &edge[i][1], &edge[i][2]);
    // 按边的权重升序排序
    qsort(edge, m, sizeof(edge[0]), cmp);

    init(n);
    int res = 0;
    int cnt = 0;
    // 凑够 n - 1 条边就可以退出
    for (int i = 0; i < m && cnt < n - 1; ++i) {
        int u = edge[i][0];
        int v = edge[i][1];
        int w = edge[i][2];
        // 两个点在一个集合里，说明已经他俩之间已经有路径了
        // 如果再把当前边加入 MST 就会出现环，所以跳过
        if (is_same_set(u, v)) continue;
        // 把两个顶点加入 MST
        unite(u, v);
        res += w;
        ++cnt;
    }

    if (cnt != n - 1) {
        printf("orz\n");
    } else {
        printf("%d\n", res);
    }

    return 0;
}
