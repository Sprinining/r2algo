#include <stdio.h>
#include <stdlib.h>

#define MOD 19650827

// 无后效性：一旦进入某个状态，未来怎么走，只取决于这个状态本身，和“怎么走到这一步的”没有关系。
// 这个 DP 的问题是：状态设计不满足无后效性，
// 因为缺少“最后一个选的人”这一关键信息，导致同一状态对应多个不同历史，从而转移错误。
// 错误解法
int dfs(int *a, int l, int r) {
    if (l >= r) return 1;
    if (l + 1 == r) return a[l] <= a[r] ? 2 : 0;
    int res = 0;
    // a[l] 最后出现
    if (a[l] <= a[l + 1]) res = ((long long)res + dfs(a, l + 2, r)) % MOD;
    if (a[l] <= a[r]) res = ((long long)res + dfs(a, l + 1, r - 1)) % MOD;
    // a[r] 最后出现
    if (a[r] >= a[l]) res = ((long long)res + dfs(a, l + 1, r - 1)) % MOD;
    if (a[r] >= a[r - 1]) res = ((long long)res + dfs(a, l, r - 2)) % MOD;
    return res % MOD;
}

int main() {
    int n;
    scanf("%d", &n);
    int *a = malloc(sizeof(*a) * n);
    for (int i = 0; i < n; ++i) scanf("%d", &a[i]);
    printf("%d", dfs(a, 0, n - 1));
}
