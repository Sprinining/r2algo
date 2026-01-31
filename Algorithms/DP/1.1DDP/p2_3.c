#include <stdio.h>

int durations[3] = {1, 7, 30};

int m1n(int a, int b) { return a < b ? a : b; }

// 自底向上
int mincostTickets(int* days, int daysSize, int* costs, int costsSize) {
    int* dp = (int*)malloc(sizeof(int) * daysSize);
    for (int i = 0; i < daysSize; i++) dp[i] = 0x7fffffff;

    // 由最简单的子问题推到原问题
    for (int i = 0; i < daysSize; i++) {
        for (int j = 0; j < 3; j++) {
            int d = days[i] - durations[j];
            int k = i;
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