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
    // 沿着斜线填
    for (int step = 1; step < n; ++step) {
        for (int l = 0, r = l + step; r < n; ++l, ++r) {
            if (s[l] == s[r]) {
                dp[l][r] = dp[l + 1][r - 1];
            } else {
                dp[l][r] = MMIN(dp[l][r - 1], dp[l + 1][r]) + 1;
            }
        }
    }

    return dp[0][n - 1];
}
