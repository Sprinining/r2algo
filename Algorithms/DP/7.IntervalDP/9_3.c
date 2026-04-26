#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MOD 19650827
#define IDX(i, j, k) ((i) * (J) * (K) + (j) * (K) + (k))

int I, J, K;
int *dp;

// flag = 0: a[l] 是最后加入的
// flag = 1: a[r] 是最后加入的
int dfs(int *a, int l, int r, int flag) {
    if (l == r) return 1;
    if (l + 1 == r) return a[l] <= a[r] ? 1 : 0;
    if (dp[IDX(l, r, flag)] != -1) return dp[IDX(l, r, flag)];
    int res = 0;
    if (flag == 0) {
        if (a[l] <= a[l + 1]) res = ((long long)res + dfs(a, l + 1, r, 0)) % MOD;
        if (a[l] <= a[r]) res = ((long long)res + dfs(a, l + 1, r, 1)) % MOD;
    } else {
        if (a[r] >= a[l]) res = ((long long)res + dfs(a, l, r - 1, 0)) % MOD;
        if (a[r] >= a[r - 1]) res = ((long long)res + dfs(a, l, r - 1, 1)) % MOD;
    }
    dp[IDX(l, r, flag)] = res;
    return res;
}

int main() {
    int n;
    scanf("%d", &n);
    int *a = malloc(sizeof(*a) * n);
    for (int i = 0; i < n; ++i) scanf("%d", &a[i]);
    I = n;
    J = n;
    K = 2;
    dp = malloc(sizeof(*dp) * I * J * K);
    memset(dp, -1, sizeof(*dp) * I * J * K);
    printf("%d", ((long long)dfs(a, 0, n - 1, 0) + dfs(a, 0, n - 1, 1)) % MOD);
}
