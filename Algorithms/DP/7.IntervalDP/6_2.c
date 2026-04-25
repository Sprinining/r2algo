#include <stdlib.h>
#include <string.h>

#define IDX(i, j, k) ((i) * (J) * (K) + (j) * (K) + (k))

int I, J, K;
int* dp;

int dfs(char* s, int l, int r, int res) {
    if (l == r) return s[l] - '0' == res ? 1 : 0;
    if (dp[IDX(l, r, res)] != -1) return dp[IDX(l, r, res)];
    int ans = 0;
    for (int i = l + 1; i < r; i += 2) {
        int l0 = dfs(s, l, i - 1, 0);
        int l1 = dfs(s, l, i - 1, 1);
        int r0 = dfs(s, i + 1, r, 0);
        int r1 = dfs(s, i + 1, r, 1);
        if (s[i] == '&' && res == 1) ans += l1 * r1;
        if (s[i] == '&' && res == 0) ans += l0 * r0 + l0 * r1 + l1 * r0;
        if (s[i] == '|' && res == 1) ans += l1 * r1 + l1 * r0 + l0 * r1;
        if (s[i] == '|' && res == 0) ans += l0 * r0;
        if (s[i] == '^' && res == 1) ans += l1 * r0 + l0 * r1;
        if (s[i] == '^' && res == 0) ans += l0 * r0 + l1 * r1;
    }
    dp[IDX(l, r, res)] = ans;
    return ans;
}

int countEval(char* s, int result) {
    int len = strlen(s);
    I = len;
    J = len;
    K = 2;
    dp = malloc(sizeof(*dp) * I * J * K);
    memset(dp, -1, sizeof(*dp) * I * J * K);
    return dfs(s, 0, strlen(s) - 1, result);
}
