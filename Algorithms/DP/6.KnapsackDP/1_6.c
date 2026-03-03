#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int mmax(int a, int b) { return a > b ? a : b; }

// 空间压缩
int main() {
    int t, m;
    scanf("%d %d", &t, &m);
    int** choice = malloc(sizeof(*choice) * m);
    int* data = malloc(sizeof(*data) * m * 2);
    for (int i = 0; i < m; i++) choice[i] = data + i * 2;
    for (int i = 0; i < m; i++) scanf("%d %d", &choice[i][0], &choice[i][1]);

    // dp[i][j] = 在前 i 个物品中选，总时间 ≤ j 时的最大价值
    int rows = m + 1;
    int columns = t + 1;
    int* dp = calloc(columns, sizeof(*dp));

    // 内层 for 可以简化，不满足 choice[i - 1][0] <= j 的就是不选
    // 满足 choice[i - 1][0] <= j 再去取较大者
    for (int i = 1; i < rows; i++)
        for (int j = columns - 1; choice[i - 1][0] <= j; j--)
            dp[j] = mmax(dp[j], dp[j - choice[i - 1][0]] + choice[i - 1][1]);

    printf("%d", dp[t]);
}