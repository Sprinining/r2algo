#include <stdlib.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))

int maxSubArray(int* nums, int numsSize) {
    // dp[i] = 以 nums[i] 结尾的子数组的最大和
    int* dp = malloc(sizeof(*dp) * numsSize);
    dp[0] = nums[0];
    int res = dp[0];
    for (int i = 1; i < numsSize; ++i) {
        // 若 dp[i-1] > 0，则扩展当前子数组
        // 否则以 nums[i] 重新开始新的子数组
        dp[i] = ((dp[i - 1] > 0) ? dp[i - 1] : 0) + nums[i];
        res = MAX(res, dp[i]);
    }

    return res;
}