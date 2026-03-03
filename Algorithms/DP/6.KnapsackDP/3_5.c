#include <stdlib.h>

// 求非负数组 nums 中，有多少个子集的累加和恰好为 m
int subsets(int* nums, int numsSize, int m) {
    // dp[j] = 前 i 个元素中选择，累加和恰好为 j 的子集个数
    int* dp = calloc(m + 1, sizeof(*dp));
    // 空集的累加和为 0，有 1 种方法
    dp[0] = 1;

    // 倒序遍历，避免覆盖
    for (int i = 1; i <= numsSize; ++i)
        for (int j = m; j >= nums[i - 1]; --j) dp[j] += dp[j - nums[i - 1]];

    return dp[m];
}

/*
    原问题：
    给定 nums 和 target
    每个数可以选择 + 或 -
    求有多少种表达式结果等于 target

    推导过程：

    设：
        A = 取正号的集合
        B = 取负号的集合

    则：
        sum(A) - sum(B) = target

    两边加上 sum(A) + sum(B)：

        sum(A) - sum(B) + sum(A) + sum(B)
        = target + sum(A) + sum(B)

    得：

        2 * sum(A) = target + 所有数的总和

    所以：

        sum(A) = (target + sum) / 2

    问题转化为：

        在 nums 中选子集，
        有多少种方法使得子集累加和为 (target + sum) / 2

    这是一个 01 背包计数问题。
*/
int findTargetSumWays(int* nums, int numsSize, int target) {
    int sum = 0;
    for (int i = 0; i < numsSize; i++) sum += nums[i];

    // target 超出 [-sum, sum]
    if (target < -sum || target > sum) return 0;
    // (target + sum) 不是偶数（无法整除 2）
    if ((target + sum) % 2 != 0) return 0;
    int m = (target + sum) / 2;

    return subsets(nums, numsSize, m);
}