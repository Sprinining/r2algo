#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long long mmax(long long a, long long b) { return a > b ? a : b; }

// 空间压缩的 01 背包
long long bag(int n, int m, int** choice) {
    int rows = n + 1;
    int columns = m + 1;
    long long* dp = calloc(columns, sizeof(*dp));

    for (int i = 1; i < rows; ++i) {
        // 从右往左避免覆盖
        for (int j = columns - 1; j > 0; --j) {
            long long p1 = dp[j];
            long long p2 = 0;
            if (j >= choice[i - 1][0]) p2 = dp[j - choice[i - 1][0]] + choice[i - 1][1];
            dp[j] = mmax(p1, p2);
        }
    }
    return dp[m];
}

int main() {
    int n, x;
    scanf("%d %d", &n, &x);
    int** choice = malloc(sizeof(*choice) * n);
    int* data = malloc(sizeof(*data) * n * 2);

    long long res = 0;
    int idx = 0;
    int money = x;
    for (int i = 0, a, b, w, c; i < n; ++i) {
        scanf("%d %d %d", &a, &b, &w);
        c = 2 * b - a;
        if (c <= 0) {
            res += w;
            money -= c;
        } else {
            choice[idx] = data + idx * 2;
            choice[idx][0] = c;
            choice[idx][1] = w;
            ++idx;
        }
    }
    res += bag(idx, money, choice);
    printf("%lld", res);
}