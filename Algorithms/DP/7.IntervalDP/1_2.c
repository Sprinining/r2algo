#include <stdlib.h>
#include <string.h>

#define MMIN(a, b) ((a) > (b) ? (b) : (a))

int** dp;
int* data;

int dfs(char* s, int l, int r) {
    // 单个字符回文；越界也不需要插入字符
    if (l >= r) return 0;
    if (dp[l][r] != -1) return dp[l][r];
    if (s[l] == s[r]) {
        // 两端字符相同时
        dp[l][r] = dfs(s, l + 1, r - 1);
    } else {
        // 两端字符不同时，两种情况，在末尾插入 s[l] 或者在开头插入 s[r]
        dp[l][r] = MMIN(dfs(s, l, r - 1), dfs(s, l + 1, r)) + 1;
    }
    return dp[l][r];
}

int minInsertions(char* s) {
    int n = strlen(s);
    dp = malloc(sizeof(*dp) * n);
    data = malloc(sizeof(*data) * n * n);
    memset(data, -1, sizeof(*data) * n * n);
    for (int i = 0; i < n; ++i) dp[i] = data + i * n;
    return dfs(s, 0, n - 1);
}