#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

bool isMatch(char* s, char* p) {
    int rows = strlen(s) + 1;
    int cols = strlen(p) + 1;

    // dp[i][j] 表示 s[i:] 是否能匹配 p[j:]
    bool** dp = malloc(rows * sizeof(*dp));
    bool* data = calloc(rows * cols, sizeof(*data));
    for (int i = 0; i < rows; ++i) dp[i] = data + i * cols;

    dp[rows - 1][cols - 1] = true;  // 空串匹配空模式

    // 空串匹配非空模式，需要处理 '*'
    for (int j = cols - 2; j >= 0; --j)
        dp[rows - 1][j] = (j + 2 < cols && p[j + 1] == '*') ? dp[rows - 1][j + 2] : false;

    // 自底向上填表
    for (int i = rows - 2; i >= 0; --i) {
        for (int j = cols - 2; j >= 0; --j) {
            bool first_match = (s[i] == p[j] || p[j] == '.');

            if (j + 2 < cols && p[j + 1] == '*') {
                // * 匹配 0 次或者多次
                dp[i][j] = dp[i][j + 2] || (first_match && dp[i + 1][j]);
            } else {
                // 普通字符匹配
                dp[i][j] = first_match && dp[i + 1][j + 1];
            }
        }
    }

    return dp[0][0];
}
