#include <stdio.h>

int durations[3] = {1, 7, 30};

int m1n(int a, int b) { return a < b ? a : b; }

// 自底向上
// O(n^2)
// 可以优化成 O(n)，用三个指针分别记录上一个覆盖范围，不必每次 while 查找
int mincostTickets(int* days, int daysSize, int* costs, int costsSize) {
    // dp[i] 表示到第 i 天（即 days[i]）的最小花费
    int* dp = malloc(sizeof(*dp) * daysSize);
    for (int i = 0; i < daysSize; i++) dp[i] = 0x7fffffff;

    // 由最简单的子问题推到原问题
    // O(n)
    for (int i = 0; i < daysSize; i++) {
        // O(3)
        for (int j = 0; j < 3; j++) {
            // 票的覆盖起点
            int d = days[i] - durations[j];
            int k = i;
            // 找到上一个不被当前票覆盖的天
            // O(n)
            while (k >= 0 && days[k] > d) k--;
            if (k < 0) {
                // 一张票就能包含所有
                dp[i] = m1n(dp[i], costs[j]);
            } else {
                // 只能包含一部分日期，再加上已经算过的子问题
                dp[i] = m1n(dp[i], costs[j] + dp[k]);
            }
        }
    }
    return dp[daysSize - 1];
}