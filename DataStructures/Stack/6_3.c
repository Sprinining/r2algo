#include <stdlib.h>

#define MMAX(a, b) ((a) > (b) ? (a) : (b))

int maxWidthRamp(int* nums, int numsSize) {
    int n = numsSize;

    int* data = malloc(sizeof(int) * n * n);
    int** dp = malloc(sizeof(int*) * n);
    for (int i = 0; i < n; ++i) dp[i] = data + i * n;

    // 依赖下方位置和左侧位置
    // 从下往上，从左往右
    for (int i = n - 1; i >= 0; --i) {
        dp[i][i] = 0;
        for (int j = i + 1; j < n; ++j) {
            if (nums[i] <= nums[j]) {
                dp[i][j] = j - i;
            } else {
                int down = i + 1 < n ? dp[i + 1][j] : 0;
                int left = j - 1 >= 0 ? dp[i][j - 1] : 0;
                dp[i][j] = MMAX(down, left);
            }
        }
    }

    return dp[0][n - 1];
}
