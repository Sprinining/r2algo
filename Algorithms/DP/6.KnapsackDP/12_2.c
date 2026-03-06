#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

char *s, *p;
int len_s, len_p;
int** dp;
int* data;

bool dfs(int i, int j) {
    // 模式串消耗完
    if (j == len_p) return i == len_s;

    if (dp[i][j] != 0) return dp[i][j] == 1;

    // 当前位置是否是 *
    if (p[j] == '*') {
        // 剪枝：有 true 就返回，而不是 p1 || p2，那样会多算
        // * 匹配 0 个
        if (dfs(i, j + 1)) {
            dp[i][j] = 1;
        } else if ((i < len_s) && dfs(i + 1, j)) {
            // * 匹配多个，前提是当前字符匹配
            dp[i][j] = 1;
        } else {
            dp[i][j] = 2;
        }
    } else {
        // 当前位置是否匹配
        bool first_match = (i < len_s) && (p[j] == s[i] || p[j] == '?');
        dp[i][j] = (first_match && dfs(i + 1, j + 1)) ? 1 : 2;
    }
    return dp[i][j] == 1;
}

bool isMatch(char* ss, char* pp) {
    s = ss;
    p = pp;
    len_s = strlen(s);
    len_p = strlen(p);
    int rows = len_s + 1;
    int cols = len_p + 1;
    dp = malloc(sizeof(*dp) * rows);
    // 初始化为 0，表示未处理过；1 表示 ture，2 表示 false
    data = calloc(rows * cols, sizeof(*data));
    for (int i = 0; i < rows; ++i) dp[i] = data + i * cols;
    return dfs(0, 0);
}