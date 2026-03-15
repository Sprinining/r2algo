int mmax(int a, int b) { return a > b ? a : b; }

int lengthOfLIS(int* nums, int numsSize) {
    // dp[i] = 必须以 nums[i] 结尾的 LIS
    int* dp = malloc(sizeof(*dp) * numsSize);
    int res = 1;

    for (int i = 0; i < numsSize; ++i) {
        dp[i] = 1;
        for (int j = i - 1; j >= 0; --j) {
            if (nums[i] > nums[j]) dp[i] = mmax(dp[i], dp[j] + 1);
        }
        res = mmax(res, dp[i]);
    }

    return res;
}