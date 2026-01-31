#include <stdio.h>

// https://leetcode.cn/problems/minimum-cost-for-tickets/

// 三种票对应的假期时长
int durations[3] = {1, 7, 30};

int m1n(int a, int b) { return a < b ? a : b; }

// 返回 days[0...n] 列出的每一天的旅行所需要的最低消费
int func(int* days, int n, int* costs) {
    if (n < 0) return 0;
    // 最低花费
    int min_sum = 0x7fffffff;

    // 假设当前日期是包含在三种票中的某一种票的时长里
    // 遍历这三种票的情况
    for (int i = 0; i < 3; i++) {
        // 以当前日期为票的时长的最后一天，计算出买票的前一天 d
        int d = days[n] - durations[i];
        int j = n;
        // 包含在 [d+1, days[n]] 内的日期都不用考虑了，都包含在刚才的票里了
        // 只需往前找到最近的一个没有被票包含的日期
        while (j >= 0 && days[j] > d) j--;
        // 计算子问题
        int before = func(days, j, costs);
        // 最低花费
        min_sum = m1n(min_sum, costs[i] + before);
    }
    return min_sum;
}

int mincostTickets(int* days, int daysSize, int* costs, int costsSize) {
    return func(days, daysSize - 1, costs);
}
