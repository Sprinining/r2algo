#include <stdbool.h>
#include <stdlib.h>

int n;
int* nums;
int each;
int* dp;

bool dfs(int stat, int cur, int left) {
    if (left == 0) return true;
    if (dp[stat] != 0) return dp[stat] == 1;
    bool res = false;
    for (int i = 0; i < n; ++i) {
        if ((stat >> i) & 1) continue;
        if (cur + nums[i] > each) continue;
        if (cur + nums[i] == each) res = dfs(stat | (1 << i), 0, left - 1);
        if (cur + nums[i] < each) res = dfs(stat | (1 << i), cur + nums[i], left);
        if (res) break;
    }
    dp[stat] = res ? 1 : -1;
    return res;
}

bool canPartitionKSubsets(int* _nums, int numsSize, int k) {
    n = numsSize;
    nums = _nums;
    int total = 0;
    for (int i = 0; i < n; ++i) total += nums[i];
    each = total / k;
    if (total % k != 0) return false;
    // 0：未设置，1：true，-1：false
    dp = calloc(1 << n, sizeof(*dp));
    return dfs(0, 0, k);
}
