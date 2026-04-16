#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MMAX(a, b) ((a) > (b) ? (a) : (b))
const int MOD = 7;

int dfs(int* nums, int numsSize, int index, int sum) {
    if (index == numsSize) return (sum % MOD) == 0 ? sum : -1;
    return MMAX(dfs(nums, numsSize, index + 1, sum + nums[index]),
                dfs(nums, numsSize, index + 1, sum));
}

// 给定一个非负数组 nums，可以任意选择数字组成子序列，但是子序列的累加和必须被 7 整除，返回最大累加和
// 暴力解
int func1(int* nums, int numsSize) { return dfs(nums, numsSize, 0, 0); }

int func2(int* nums, int numsSize) {
    int rows = numsSize + 1;
    int cols = MOD;
    // dp[i][j] 表示 nums 前 i 个数的子序列累加和 %7 后等于 j 的最大累加和
    int** dp = (int**)malloc(sizeof(*dp) * rows);
    int* data = (int*)malloc(sizeof(*data) * rows * cols);
    // 初始化为 -1，表示不存在
    memset(data, -1, sizeof(*data) * rows * cols);
    for (int i = 0; i < rows; ++i) dp[i] = data + i * cols;

    // **在子序列问题中，空集作为初始状态，其和定义为 0，是所有状态转移的基础，否则 DP 无法展开
    dp[0][0] = 0;
    for (int i = 1; i < rows; ++i) {
        int num = nums[i - 1];
        // 当前的余数
        int remainder = num % MOD;
        for (int j = 0; j < cols; ++j) {
            // 情况 1：不用 num
            dp[i][j] = dp[i - 1][j];
            // 情况 2：使用 num，需要找到上一个状态的余数 beofore，使得 (remainder + before) % MOD = j
            int before = (j - remainder + MOD) % MOD;
            // 如果存在就有可能更新
            if (dp[i - 1][before] != -1) {
                dp[i][j] = MMAX(dp[i][j], dp[i - 1][before] + num);
            }
        }
    }

    return dp[rows - 1][0];
}

bool judge() {
    int numsSize = 10;
    int* nums = (int*)malloc(sizeof(*nums) * numsSize);
    for (int i = 0; i < numsSize; ++i) {
        // [0, 9]
        nums[i] = rand() % 10;
    }

    int r1 = func1(nums, numsSize);
    int r2 = func2(nums, numsSize);
    if (r1 != r2) {
        printf("error: func1=%d func2=%d\n", r1, r2);
        return false;
    }

    return true;
}

int main() {
    srand(time(NULL));
    int trials = 10000;
    for (int i = 0; i < trials; ++i) {
        if (!judge()) exit(EXIT_FAILURE);
    }
    printf("all success\n");
}