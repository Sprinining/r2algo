#include <stdlib.h>
#include <string.h>

#define MOD 1000000007

int** dp;
int* data;

// 空间压缩
int profitableSchemes(int n, int minProfit, int* group, int groupSize, int* profit,
                      int profitSize) {
    int layers = groupSize + 1;
    int rows = n + 1;
    int cols = minProfit + 1;
    dp = malloc(sizeof(*dp) * rows);
    data = calloc(rows * cols, sizeof(*data));
    for (int i = 0; i < rows; ++i) {
        dp[i] = data + i * cols;
        dp[i][0] = 1;
    }

    for (int l = 1; l < layers; ++l) {
        int g = group[l - 1];
        int p = profit[l - 1];
        for (int i = rows - 1; i >= 0; --i) {
            for (int j = cols - 1; j >= 0; --j) {
                int pre = j > p ? j - p : 0;
                if (i >= g) dp[i][j] = ((long long)dp[i][j] + dp[i - g][pre]) % MOD;
            }
        }
    }

    return dp[n][minProfit];
}
