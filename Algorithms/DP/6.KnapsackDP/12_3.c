#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

bool isMatch(char* s, char* p) {
    int rows = strlen(s) + 1;
    int cols = strlen(p) + 1;
    // dp[i][j] = s[i:] 与 p[j:] 是否完全匹配
    bool** dp = malloc(sizeof(*dp) * rows);
    // 初始化为 0，表示未处理过；1 表示 ture，2 表示 false
    bool* data = calloc(rows * cols, sizeof(*data));
    for (int i = 0; i < rows; ++i) dp[i] = data + i * cols;

    // 最后一列，只有最后一个是 true，其他 false
    dp[rows - 1][cols - 1] = true;
    // 最后一行
    for (int j = cols - 2; j >= 0; --j) dp[rows - 1][j] = (p[j] == '*') && dp[rows - 1][j + 1];

    for (int i = rows - 2; i >= 0; --i) {
        for (int j = cols - 2; j >= 0; --j) {
            if (p[j] == '*') {
                // * 不匹配
                bool p1 = dp[i][j + 1];
                // * 匹配
                bool p2 = dp[i + 1][j];
                dp[i][j] = p1 || p2;
            } else {
                bool cur_match = (s[i] == p[j]) || (p[j] == '?');
                // 当前字符匹配且后续也匹配
                dp[i][j] = cur_match && dp[i + 1][j + 1];
            }
        }
    }

    return dp[0][0];
}