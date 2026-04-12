#include <stdlib.h>

#define MMAX(a, b) ((a) > (b) ? (a) : (b))

// 允许数组中有负数，要避免负收益
int rob(int* nums, int numsSize) {
    if (numsSize == 1) return MMAX(nums[0], 0);
    int* dp = malloc(sizeof(*dp) * numsSize);
    // 一开始就保证 dp 永远 ≥ 0，是负收益就不偷
    dp[0] = MMAX(nums[0], 0);
    dp[1] = MMAX(dp[0], nums[1]);
    for (int i = 2; i < numsSize; ++i) {
        // 当前位置偷不偷两种情况
        dp[i] = MMAX(dp[i - 2] + nums[i], dp[i - 1]);
    }

    return dp[numsSize - 1];
}