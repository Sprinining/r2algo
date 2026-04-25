#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MMIN(a, b) ((a) > (b) ? (b) : (a))

int **dp;
int *data;

int dfs(char *s, int l, int r) {
    if (l > r) return 0;
    if (l == r) return 1;
    if (dp[l][r] != -1) return dp[l][r];
    int res = 0x7fffffff;
    // 情况1：作为一个整体
    if ((s[l] == '(' && s[r] == ')') || (s[l] == '[' && s[r] == ']')) res = dfs(s, l + 1, r - 1);
    // 情况2：作为两个并列的部分
    for (int m = l; m < r; ++m) {
        res = MMIN(res, dfs(s, l, m) + dfs(s, m + 1, r));
    }
    dp[l][r] = res;
    return res;
}

int main() {
    char *s = malloc(sizeof(*s) * 101);
    scanf("%s", s);

    int len = strlen(s);
    dp = malloc(sizeof(*dp) * len);
    data = malloc(sizeof(*data) * len * len);
    memset(data, -1, sizeof(*data) * len * len);
    for (int i = 0; i < len; ++i) dp[i] = data + i * len;

    printf("%d", dfs(s, 0, len - 1));
}
