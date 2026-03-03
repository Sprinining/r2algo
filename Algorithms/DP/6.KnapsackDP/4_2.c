#include <stdlib.h>
#include <string.h>

int mmax(int a, int b) { return a > b ? a : b; }

// 空间压缩
int lastStoneWeightII(int* stones, int stonesSize) {
    int sum = 0;
    for (int i = 0; i < stonesSize; ++i) sum += stones[i];
    int limit = sum / 2;
    int rows = stonesSize + 1;
    int cols = limit + 1;

    int* dp = calloc(cols, sizeof(*dp));
    for (int i = 1; i < rows; ++i) {
        for (int j = cols - 1; j >= stones[i - 1]; --j) {
            dp[j] = mmax(dp[j], dp[j - stones[i - 1]] + stones[i - 1]);
        }
    }

    int small = dp[cols - 1];
    return sum - 2 * small;
}
