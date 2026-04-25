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

int minCost(int n, int *cuts, int cutsSize) {
    qsort(cuts, cutsSize, sizeof(*cuts), cmp);
    int len = cutsSize + 2;
    int *arr = malloc(sizeof(*arr) * len);
    // 头尾各插入一个，方便计算每次切割的成本
    arr[0] = 0;
    arr[len - 1] = n;
    for (int i = 0; i < cutsSize; ++i) arr[i + 1] = cuts[i];
    dp = malloc(sizeof(*dp) * len);
    data = calloc(len * len, sizeof(*data));
    for (int i = 0; i < len; ++i) dp[i] = data + i * len;

    for (int l = len - 3; l >= 0; --l) {
        for (int r = l + 2; r < len; ++r) {
            int cost = arr[r] - arr[l];
            int res = 0x7fffffff;
            for (int m = l + 1; m < r; ++m) {
                res = MMIN(res, cost + dp[l][m] + dp[m][r]);
            }
            dp[l][r] = res;
        }
    }

    return dp[0][len - 1];
}
