#include <stdbool.h>
#include <stdlib.h>

int m1n(int a, int b) { return a < b ? a : b; }

int min3(int a, int b, int c) { return m1n(m1n(a, b), c); }

int nthUglyNumber(int n) {
    // dp[i] 就是第 i 个丑数
    int* dp = (int*)malloc(sizeof(int) * (n + 1));
    dp[1] = 1;
    int i = 2, i2 = 1, i3 = 1, i5 = 1;
    while (i <= n) {
        // 获得三个丑数
        // 如果 val2 不是序列中的下一个，那么 i2 就不会递增，因为 dp[i2] * 2
        // 还没出现在序列中，更不会轮到 dp[i2+1] * 2
        int val2 = dp[i2] * 2;
        // 如果 val3 是序列中的下一个，那么 i3 就需要递增，因为 dp[i3+1] * 3
        // 仍可能比 val2 和 val5 都小
        int val3 = dp[i3] * 3;
        int val5 = dp[i5] * 5;
        // 当前的丑数就是由之前的丑数乘 2 或 3 或 5 得到的
        int m = min3(val2, val3, val5);
        // 最小的就是递增序列中的下一个
        dp[i++] = m;
        // 对应的下标后移一位
        if (m == val2) i2++;
        if (m == val3) i3++;
        if (m == val5) i5++;
    }

    return dp[n];
}