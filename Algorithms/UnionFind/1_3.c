#include <stdbool.h>
#include <stdio.h>

#define MAXN 200000

// 元素编号从 1 开始
int father[MAXN + 1];
// rank 是树的估计高度，不是实时高度，可能比实际树高大
int rank[MAXN + 1];
int stk[MAXN + 1];
int top;

void build(int n) {
    // 初始时每个元素都是一个集合
    for (int i = 1; i <= n; ++i) {
        father[i] = i;
        rank[i] = 1;
    }
    top = 0;
}

// 迭代
int find(int x) {
    // 保存路径上的元素
    while (father[x] != x) {
        stk[top++] = x;
        x = father[x];
    }

    // 路径压缩，降低树高
    while (top != 0) {
        father[stk[--top]] = x;
    }
    return x;
}

bool isSameSet(int a, int b) { return find(a) == find(b); }

void merge(int a, int b) {
    int fa = find(a);
    int fb = find(b);
    // 在同一个集合
    if (fa == fb) return;
    // 低秩挂高秩
    if (rank[fa] > rank[fb]) {
        father[fb] = fa;
    } else if (rank[fb] > rank[fa]) {
        father[fa] = fb;
    } else {
        father[fb] = fa;
        ++rank[fa];
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
