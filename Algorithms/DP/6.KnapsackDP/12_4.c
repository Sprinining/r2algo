#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

bool isMatch(char* s, char* p) {
    int rows = strlen(s) + 1;
    int cols = strlen(p) + 1;
    // dp[i][j] = s 前 i 个字符与 p 前 j 个字符是否匹配
    bool** dp = malloc(sizeof(*dp) * rows);
    bool* data = calloc(rows * cols, sizeof(*data));
    for (int i = 0; i < rows; ++i) dp[i] = data + i * cols;

    // 第一列，除了第一个为 true，其他都为 false
    dp[0][0] = true;
    // 第一行
    for (int j = 1; j < cols; ++j) dp[0][j] = (p[j - 1] == '*') && dp[0][j - 1];

    for (int i = 1; i < rows; ++i) {
        for (int j = 1; j < cols; ++j) {
            if (p[j - 1] == '*') {
                // * 匹配 0 个
                bool p1 = dp[i][j - 1];
                // * 匹配多个
                bool p2 = dp[i - 1][j];
                dp[i][j] = p1 || p2;
            } else {
                bool cur_match = (s[i - 1] == p[j - 1]) || (p[j - 1] == '?');
                // 当前字符匹配且之前的也匹配
                dp[i][j] = cur_match && dp[i - 1][j - 1];
            }
        }
    }

    return dp[rows - 1][cols - 1];
}