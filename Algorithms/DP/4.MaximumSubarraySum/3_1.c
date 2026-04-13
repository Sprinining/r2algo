#include <stdlib.h>
#define MMAX(a, b) ((a) > (b) ? (a) : (b))

// 暴力解
int maxSubarraySumCircular(int* nums, int numsSize) {
    int* dp = malloc(sizeof(*dp) * numsSize);
    int res = nums[0];
    // 枚举每个起点 k
    for (int k = 0; k < numsSize; ++k) {
        dp[0] = nums[k];
        res = MMAX(res, dp[0]);
        for (int i = 1; i < numsSize; ++i) {
            if (dp[i - 1] > 0) {
                dp[i] = dp[i - 1] + nums[(k + i) % numsSize];
            } else {
                dp[i] = nums[(k + i) % numsSize];
            }
            res = MMAX(res, dp[i]);
        }
    }

    return res;
}