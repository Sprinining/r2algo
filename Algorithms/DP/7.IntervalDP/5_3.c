#include <stdio.h>
#include <stdlib.h>

#define MMAX(a, b) ((a) > (b) ? (a) : (b))

int** dp;
int* data;

int maxCoins(int* nums, int numsSize) {
    int len = numsSize + 2;
    int* a = malloc(sizeof(*a) * len);
    a[0] = 1;
    a[len - 1] = 1;
    for (int i = 0; i < numsSize; ++i) a[i + 1] = nums[i];
    dp = malloc(sizeof(*dp) * len);
    data = calloc(len * len, sizeof(*data));
    for (int i = 0; i < len; ++i) dp[i] = data + i * len;

    // [i, i] 上最后打爆 a[i]，前提是两侧 a[i-1] 和 a[i+1] 都没爆
    for (int i = 1; i <= len - 2; ++i) dp[i][i] = a[i - 1] * a[i] * a[i + 1];
    // 从下往上，从左往右填
    for (int l = len - 3; l >= 1; --l) {
        for (int r = l + 1; r <= len - 2; ++r) {
            int res = 0;
            for (int m = l; m <= r; ++m) {
                res = MMAX(res, a[l - 1] * a[m] * a[r + 1] + dp[l][m - 1] + dp[m + 1][r]);
            }
            dp[l][r] = res;
        }
    }
    return dp[1][len - 2];
}
