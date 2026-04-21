#include <stdlib.h>
#include <string.h>

#define MOD 1000000007

int*** dp;
int** plane;
int* data;

int profitableSchemes(int n, int minProfit, int* group, int groupSize, int* profit,
                      int profitSize) {
    int layers = groupSize + 1;
    int rows = n + 1;
    int cols = minProfit + 1;
    // dp[i][j][k] = 前 i 个工作里选择，在 j 人可选且至少获利 k 的情况下的可能数
    dp = malloc(sizeof(*dp) * layers);
    plane = malloc(sizeof(*plane) * layers * rows);
    data = calloc(layers * rows * cols, sizeof(*data));
    for (int i = 0; i < layers; ++i) {
        dp[i] = plane + i * rows;
        for (int j = 0; j < rows; ++j) {
            dp[i][j] = data + (i * rows * cols + j * cols);
        }
    }
    // **初始化：每一层都依赖于上一层，所以对 0 层进行初始化
    for (int j = 0; j < rows; ++j) dp[0][j][0] = 1;
    for (int i = 1; i < layers; ++i) {
        int g = group[i - 1];
        int p = profit[i - 1];
        for (int j = 0; j < rows; ++j) {
            for (int k = 0; k < cols; ++k) {
                dp[i][j][k] = dp[i - 1][j][k];
                if (j >= g) {
                    int pre = k > p ? k - p : 0;
                    dp[i][j][k] = ((long long)dp[i][j][k] + dp[i - 1][j - g][pre]) % MOD;
                }
            }
        }
    }

    return dp[groupSize][n][minProfit];
}