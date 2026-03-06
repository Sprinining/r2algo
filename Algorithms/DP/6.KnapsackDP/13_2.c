#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int mmin(int a, int b) { return a > b ? b : a; }

int main() {
    int n, h;
    scanf("%d%d", &n, &h);

    int (*hays)[2] = malloc(sizeof(*hays) * n);
    // 最大的草堆
    int max_hay = 0;
    for (int i = 0; i < n; ++i) {
        scanf("%d%d", &hays[i][0], &hays[i][1]);
        if (hays[i][0] > max_hay) max_hay = hays[i][0];
    }

    int rows = n + 1;
    // 背包扩容
    int cols = h + 1 + max_hay;
    int* dp = malloc(sizeof(*dp) * cols);

    // 初始化第一行
    dp[0] = 0;
    // 第一行处理 0 下标，其他位置都代表实现不了
    for (int j = 1; j < cols; ++j) dp[j] = 0x7fffffff;

    for (int i = 1; i < rows; ++i) {
        int w = hays[i - 1][0];
        int c = hays[i - 1][1];
        // 内存循环从 0 开始
        for (int j = 0; j < cols; ++j) {
            if (w <= j && dp[j - w] != 0x7fffffff) dp[j] = mmin(dp[j], dp[j - w] + c);
        }
    }

    int res = 0x7fffffff;
    for (int j = h; j < cols; ++j) res = mmin(res, dp[j]);
    printf("%d", res);
}