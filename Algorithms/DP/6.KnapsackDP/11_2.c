#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

char *s, *p;
int len_s, len_p;
int** dp;
int* data;

// 返回 s[i:] 和 p[j:] 是否匹配
bool dfs(int i, int j) {
    // 1. 模式串消耗完，只有当字符串也结束才算匹配成功
    if (j == len_p) return i == len_s;

    if (dp[i][j] != 0) return dp[i][j] == 1;

    // 2. 当前字符是否匹配
    bool first_match = (i < len_s) && (s[i] == p[j] || p[j] == '.');

    // 3. 判断模式串下一个字符是不是 *
    if (j + 1 < len_p && p[j + 1] == '*') {
        // * 匹配 0 次，跳过 p[j] 和 *
        bool p1 = dfs(i, j + 2);
        // * 匹配多次，前提是当前字符能匹配
        bool p2 = first_match && dfs(i + 1, j);
        dp[i][j] = p1 || p2 ? 1 : 2;
    } else {
        // 4. 普通字符匹配
        dp[i][j] = (first_match && dfs(i + 1, j + 1)) ? 1 : 2;
    }
    return dp[i][j] == 1;
}

bool isMatch(char* ss, char* pp) {
    s = ss;
    p = pp;
    len_s = strlen(s);
    len_p = strlen(p);

    // 0 表示未处理过，1 表示 ture，2 表示 false
    dp = malloc(sizeof(*dp) * (len_s + 1));
    data = calloc((len_s + 1) * (len_p + 1), sizeof(*data));
    for (int i = 0; i <= len_s; ++i) dp[i] = data + i * (len_p + 1);

    return dfs(0, 0);
}
