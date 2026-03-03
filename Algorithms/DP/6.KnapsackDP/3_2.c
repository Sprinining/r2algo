#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OFFSET 1000
int** dp;
int* data;

// 后缀式 + 记忆化搜索
// sum 可能是负数，要加上偏移量
int func(int* nums, int n, int target, int idx, int sum) {
    if (idx == n) return sum == target ? 1 : 0;
    if (dp[idx][sum + OFFSET] != -1) return dp[idx][sum + OFFSET];
    dp[idx][sum + OFFSET] = func(nums, n, target, idx + 1, sum + nums[idx]) +
                            func(nums, n, target, idx + 1, sum - nums[idx]);
    return dp[idx][sum + OFFSET];
}

int findTargetSumWays(int* nums, int numsSize, int target) {
    int rows = numsSize + 1;
    // 加上偏移量
    int columns = 1001 + OFFSET;
    // dp[idx][sum+OFFSET] = 从第 idx 个元素开始，当前累计和为 sum 的情况下，能得到最终 target 的方法数
    dp = malloc(sizeof(*dp) * rows);
    data = malloc(sizeof(*data) * rows * columns);
    for (int i = 0; i < rows; i++) {
        dp[i] = data + i * columns;
        memset(dp[i], -1, sizeof(*dp[i]) * columns);
    }

    return func(nums, numsSize, target, 0, 0);
}