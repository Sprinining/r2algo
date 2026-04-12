#include <stdlib.h>

#define MMAX(a, b) ((a) > (b) ? (a) : (b))

// 不能选相邻元素的最大累加和问题
int rob(int* nums, int numsSize) {
    if (numsSize == 1) return nums[0];
    if (numsSize == 2) return MMAX(nums[0], nums[1]);
    int* dp = malloc(sizeof(*dp) * numsSize);
    dp[0] = nums[0];
    dp[1] = MMAX(nums[0], nums[1]);
    for (int i = 2; i < numsSize; ++i) {
        // 当前位置偷不偷两种情况
        dp[i] = MMAX(dp[i - 2] + nums[i], dp[i - 1]);
    }

    return dp[numsSize - 1];
}