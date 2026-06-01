#include <stdlib.h>

#define MMAX(a, b) ((a) > (b) ? (a) : (b))

int maxWidthRamp(int* nums, int numsSize) {
    int n = numsSize;
    int* dp = malloc(sizeof(int) * n);

    // 依赖下方位置和左侧位置
    // 从下往上，从左往右
    for (int i = n - 1; i >= 0; --i) {
        dp[i] = 0;
        for (int j = i + 1; j < n; ++j) {
            if (nums[i] <= nums[j]) {
                dp[j] = j - i;
            } else {
                int down = i + 1 < n ? dp[j] : 0;
                int left = j - 1 >= 0 ? dp[j - 1] : 0;
                dp[j] = MMAX(dp[j], left);
            }
        }
    }

    return dp[n - 1];
}
