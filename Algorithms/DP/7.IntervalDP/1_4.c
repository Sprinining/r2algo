#include <stdlib.h>
#include <string.h>

#define MMIN(a, b) ((a) > (b) ? (b) : (a))

int** dp;
int* data;

int minInsertions(char* s) {
    int n = strlen(s);
    dp = malloc(sizeof(*dp) * n);
    // len = 1 的子串是 dp 的起始点；下三角矩阵中也有些是起点
    data = calloc(n * n, sizeof(*data));
    for (int i = 0; i < n; ++i) dp[i] = data + i * n;

    // 依赖于左侧，下方，左下方的格子
    // 从下往上，从左往右填
    for (int i = n - 2; i >= 0; --i) {
        for (int j = i + 1; j < n; ++j) {
            if (s[i] == s[j]) {
                dp[i][j] = dp[i + 1][j - 1];
            } else {
                dp[i][j] = MMIN(dp[i + 1][j], dp[i][j - 1]) + 1;
            }
        }
    }

    return dp[0][n - 1];
}
