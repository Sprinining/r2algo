#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

bool isMatch(char* s, char* p) {
    int rows = strlen(s) + 1;
    int cols = strlen(p) + 1;

    // 字符串 s 的前 i 个字符能否匹配模式 p 的前 j 个字符
    bool** dp = malloc(rows * sizeof(*dp));
    bool* data = calloc(rows * cols, sizeof(*data));
    for (int i = 0; i < rows; ++i) dp[i] = data + i * cols;

    // 空串匹配空模式
    dp[0][0] = true;

    // 空串匹配非空模式，需要处理 * 可以匹配 0 次
    for (int j = 2; j < cols; ++j)
        if (p[j - 1] == '*') dp[0][j] = dp[0][j - 2];

    // 自上向下填表（前缀 DP）
    for (int i = 1; i < rows; ++i) {
        for (int j = 1; j < cols; ++j) {
            if (p[j - 1] != '*') {
                // 普通字符或 '.'
                dp[i][j] = (s[i - 1] == p[j - 1] || p[j - 1] == '.') && dp[i - 1][j - 1];
            } else {
                // * 匹配 0 次
                dp[i][j] = dp[i][j - 2];
                // * 匹配多次
                if (s[i - 1] == p[j - 2] || p[j - 2] == '.') {
                    dp[i][j] |= dp[i - 1][j];
                }
            }
        }
    }

    return dp[rows - 1][cols - 1];
}