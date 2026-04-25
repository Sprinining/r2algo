#include <stdlib.h>

#define MMIN(a, b) ((a) > (b) ? (b) : (a))

int dfs(int* v, int l, int r) {
    // 构成不了三角形
    if (l + 1 >= r) return 0;
    // 大于等于三个点
    int res = 0x7fffffff;
    for (int i = l + 1; i < r; ++i) {
        res = MMIN(res, v[l] * v[i] * v[r] + dfs(v, l, i) + dfs(v, i, r));
    }
    return res;
}

int minScoreTriangulation(int* values, int valuesSize) { return dfs(values, 0, valuesSize - 1); }
