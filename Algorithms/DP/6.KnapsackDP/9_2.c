#include <stdlib.h>
#include <string.h>

int mmax(int a, int b) { return a > b ? a : b; }

// 省去结构体
int maxValueOfCoins(int** piles, int pilesSize, int* pilesColSize, int limit) {
    int rows = pilesSize + 1;
    int cols = limit + 1;
    int* dp = calloc(cols, sizeof(*dp));
    for (int i = 1; i < rows; ++i) {
        for (int j = cols - 1; j > 0; --j) {
            int p = dp[j];
            // 硬币前缀和
            int presum = 0;
            for (int k = 0; k < pilesColSize[i - 1]; ++k) {
                int cost = k + 1;
                presum += piles[i - 1][k];
                if (cost <= j) p = mmax(p, dp[j - cost] + presum);
            }
            dp[j] = p;
        }
    }

    return dp[cols - 1];
}