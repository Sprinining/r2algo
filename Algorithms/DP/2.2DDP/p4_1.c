#include <stdio.h>

int MOD = 1e9 + 7;
int m, n;

long long func(int n, int m) {
    if (n == 0) return 1;
    if (m == 0) return 0;
    // 根节点用掉了一个
    // 剩下 n - 1 个节点，分给左右子树
    long long res = 0;
    for (int i = 0; i < n; i++) {
        // 左右子树的情况相乘
        res = (res + (func(i, m - 1) * func(n - 1 - i, m - 1) % MOD)) % MOD;
    }
    return res;
}

int main() {
    scanf("%d %d", &n, &m);
    printf("%d", (int)func(n, m));
    return 0;
}