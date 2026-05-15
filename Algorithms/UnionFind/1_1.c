#include <stdbool.h>
#include <stdio.h>

#define MAXN 200000

// 元素编号从 1 开始
int father[MAXN + 1];
// 记录集合元素个数
int sz[MAXN + 1];

void build(int n) {
    // 初始时每个元素都是一个集合
    for (int i = 1; i <= n; ++i) {
        father[i] = i;
        sz[i] = 1;
    }
}

int find(int x) {
    if (father[x] == x) return x;
    // 路径压缩，降低树高
    return father[x] = find(father[x]);
}

bool isSameSet(int a, int b) { return find(a) == find(b); }

void merge(int a, int b) {
    int fa = find(a);
    int fb = find(b);
    // 在同一个集合
    if (fa == fb) return;
    // 小集合挂在大集合下面
    if (sz[fa] > sz[fb]) {
        father[fb] = fa;
        sz[fa] += sz[fb];
    } else {
        father[fa] = fb;
        sz[fb] += sz[fa];
    }
}

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    build(n);
    for (int i = 0, z, x, y; i < m; ++i) {
        scanf("%d%d%d", &z, &x, &y);
        if (z == 1) {
            merge(x, y);
        } else if (z == 2) {
            printf("%c\n", isSameSet(x, y) ? 'Y' : 'N');
        }
    }
}
