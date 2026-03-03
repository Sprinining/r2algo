#include <stdlib.h>
#include <string.h>

int findTargetSumWays(int* nums, int numsSize, int target) {
    int OFFSET = 0;
    for (int i = 0; i < numsSize; ++i) OFFSET += nums[i];
    if (target > OFFSET || target < -OFFSET) return 0;

    int rows = numsSize + 1;
    int columns = 2 * OFFSET + 1;
    // sum 范围 [-OFFSET, OFFSET]，要平移到 j 范围 [0, 2*OFFSET]
    // dp[i][sum + OFFSET] = 前 i 个数的所有组合中，累加和为 sum 的方法数
    int** dp = malloc(sizeof(*dp) * rows);
    int* data = calloc(rows * columns, sizeof(*data));
    for (int i = 0; i < rows; ++i) dp[i] = data + i * columns;

    dp[0][0 + OFFSET] = 1;
    for (int i = 1; i < rows; ++i) {
        int val = nums[i - 1];
        // 每一行的 sum 其实有实际的范围 [-cur_offset, cur_offset]
        // cur_offset 是前 i 个数的和
        for (int sum = -OFFSET; sum <= OFFSET; ++sum) {
            int p1 = 0, p2 = 0;
            // 加
            if (sum - val >= -OFFSET) p1 = dp[i - 1][sum - val + OFFSET];
            // 减
            if (sum + val <= OFFSET) p2 = dp[i - 1][sum + val + OFFSET];
            dp[i][sum + OFFSET] = p1 + p2;
        }
    }

    return dp[numsSize][target + OFFSET];
}