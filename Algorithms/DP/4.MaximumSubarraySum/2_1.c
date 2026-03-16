int max(int a, int b) { return a > b ? a : b; }

int rob(int* nums, int numsSize) {
    if (numsSize == 1) return nums[0];
    // dp[i]表示偷i间房子的最大金额
    int dp[numsSize];
    dp[0] = nums[0];
    dp[1] = max(nums[0], nums[1]);

    for (int i = 2; i < numsSize; ++i) {
        // 当前位置偷，dp[i] = dp[i-2] + nums[i]
        // 当前位置不偷，dp[i] = dp[i-1]
        dp[i] = max(dp[i - 1], dp[i - 2] + nums[i]);
    }

    return dp[numsSize - 1];
}