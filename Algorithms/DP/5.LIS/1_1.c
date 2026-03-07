#include <vector>

using namespace std;

class Solution {
public:
    // 时间复杂度 O(n^2)
    int lengthOfLIS(vector<int> &nums) {
        int n = nums.size();
        // dp[i]: 以 nums[i] 结尾的最长递增子序列
        vector<int> dp(n);
        int res = 0;
        for (int i = 0; i < n; ++i) {
            dp[i] = 1;
            for (int j = 0; j < i; ++j) {
                if (nums[j] < nums[i])
                    dp[i] = max(dp[i], dp[j] + 1);
            }
            res = max(res, dp[i]);
        }
        return res;
    }
};