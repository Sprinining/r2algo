#include <stdlib.h>
#include <string.h>

#define MMIN(a, b) ((a) > (b) ? (b) : (a))

int** dp;
int* data;

int dfs(int* v, int l, int r) {
    // 构成不了三角形
    if (l + 1 >= r) return 0;
    if (dp[l][r] != -1) return dp[l][r];
    // 大于等于三个点
    int res = 0x7fffffff;
    for (int i = l + 1; i < r; ++i) {
        res = MMIN(res, v[l] * v[i] * v[r] + dfs(v, l, i) + dfs(v, i, r));
    }
    dp[l][r] = res;
    return res;
}

int minScoreTriangulation(int* values, int valuesSize) {
    dp = malloc(sizeof(*dp) * valuesSize);
    data = malloc(sizeof(*data) * valuesSize * valuesSize);
    memset(data, -1, sizeof(*data) * valuesSize * valuesSize);
    for (int i = 0; i < valuesSize; ++i) dp[i] = data + i * valuesSize;
    return dfs(values, 0, valuesSize - 1);
}
