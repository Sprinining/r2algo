#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MOD 1000000007

char *s;
int *left, *right;
int **dp;
int *data;
int n;

int dfs(int i, int j) {
    if (i > j) return 0;   // 空区间
    if (i == j) return 1;  // 单字符

    if (dp[i][j] != -1) return dp[i][j];

    int res = 0;
    if (s[i] != s[j]) {
        // [i,j-1] + [i+1,j] - [i+1,j-1]
        res = (((long long)dfs(i, j - 1) + dfs(i + 1, j)) % MOD);
        res = (((long long)res - dfs(i + 1, j - 1) + MOD) % MOD);
    } else {
        int l = right[i];  // i 右侧最近相同字符
        int r = left[j];   // j 左侧最近相同字符

        if (l > r) {
            // 中间没有和 s[i] 相同字符
            // 内部 *2 + "a" + "aa"
            res = (((long long)dfs(i + 1, j - 1) * 2 + 2) % MOD);
        } else if (l == r) {
            // 中间只有一个
            // 内部 *2 + "aa"
            res = (((long long)dfs(i + 1, j - 1) * 2 + 1) % MOD);
        } else {
            // 中间多个
            // 内部 *2 - 去掉重复部分
            res = (((long long)dfs(i + 1, j - 1) * 2 - dfs(l + 1, r - 1) + MOD) % MOD);
        }
    }

    return dp[i][j] = res;
}

int countPalindromicSubsequences(char *str) {
    s = str;
    n = strlen(str);

    left = malloc(sizeof(*left) * n);
    right = malloc(sizeof(*right) * n);

    dp = malloc(sizeof(*dp) * n);
    data = malloc(sizeof(*data) * n * n);
    memset(data, -1, sizeof(*data) * n * n);
    for (int i = 0; i < n; i++) dp[i] = data + i * n;

    int last[256];

    // left[i] = s[i] 在 i 左边最近一次出现的位置
    for (int i = 0; i < 256; ++i) last[i] = -1;
    for (int i = 0; i < n; ++i) {
        left[i] = last[s[i]];
        // 记录最近出现的位置
        last[s[i]] = i;
    }

    for (int i = 0; i < 256; ++i) last[i] = n;
    for (int i = n - 1; i >= 0; --i) {
        right[i] = last[s[i]];
        last[s[i]] = i;
    }

    return dfs(0, n - 1);
}
