#include <stdlib.h>
#include <string.h>

#define MMIN(a, b) ((a) > (b) ? (b) : (a))

int **dp;
int *data;

int cmp(const void *a, const void *b) {
    int x = *(int *)a;
    int y = *(int *)b;
    if (x < y) return -1;
    if (x > y) return 1;
    return 0;
}

int dfs(int *a, int l, int r) {
    if (l + 1 == r) return 0;
    if (dp[l][r] != -1) return dp[l][r];
    int cost = a[r] - a[l];
    // [l+1, r-1] 上选取切割点
    int res = 0x7fffffff;
    for (int m = l + 1; m < r; ++m) {
        res = MMIN(res, cost + dfs(a, l, m) + dfs(a, m, r));
    }
    dp[l][r] = res;
    return res;
}

int minCost(int n, int *cuts, int cutsSize) {
    qsort(cuts, cutsSize, sizeof(*cuts), cmp);
    int len = cutsSize + 2;
    int *arr = malloc(sizeof(*arr) * len);
    // 头尾各插入一个，方便计算每次切割的成本
    arr[0] = 0;
    arr[len - 1] = n;
    for (int i = 0; i < cutsSize; ++i) arr[i + 1] = cuts[i];
    dp = malloc(sizeof(*dp) * len);
    data = malloc(sizeof(*data) * len * len);
    memset(data, -1, sizeof(*data) * len * len);
    for (int i = 0; i < len; ++i) dp[i] = data + i * len;
    return dfs(arr, 0, len - 1);
}
