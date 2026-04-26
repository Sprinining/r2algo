#include <stdlib.h>
#include <string.h>

#define MMIN(a, b) ((a) > (b) ? (b) : (a))

int** dp;
int* data;

int dfs(char* s, int l, int r) {
    if (l == r) return 1;
    if (dp[l][r] != -1) return dp[l][r];
    // 两端相同，问题等价于求 [l, r-1] 位置上的
    if (s[l] == s[r]) return dfs(s, l, r - 1);
    // 两端不同，说明两端不可能是在一次印刷中完成的，中间必有一个划分点
    // 枚举划分点的可能
    int res = 0x7fffffff;
    for (int m = l; m < r; ++m) {
        res = MMIN(res, dfs(s, l, m) + dfs(s, m + 1, r));
    }
    dp[l][r] = res;
    return res;
}

int strangePrinter(char* s) {
    int len = strlen(s);
    dp = malloc(sizeof(*dp) * len);
    data = malloc(sizeof(*data) * len * len);
    memset(data, -1, sizeof(*data) * len * len);
    for (int i = 0; i < len; ++i) dp[i] = data + i * len;
    return dfs(s, 0, len - 1);
}
