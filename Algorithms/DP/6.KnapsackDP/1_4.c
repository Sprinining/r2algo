#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int mmax(int a, int b) { return a > b ? a : b; }

// 前缀式 + 自底向上
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
    int** dp = malloc(sizeof(*dp) * rows);
    int* data2 = calloc(rows * columns, sizeof(*data2));
    for (int i = 0; i < rows; i++) dp[i] = data2 + i * columns;

    // 第一行第一列都是 0，不用考虑

    for (int i = 1; i < rows; i++) {
        for (int j = 1; j < columns; j++) {
            // 最后一个物品 choice[i-1] 选还是不选
            int* item = choice[i - 1];
            // 不选
            int p1 = dp[i - 1][j];
            // 选
            int p2 = 0;
            if (item[0] <= j) p2 = dp[i - 1][j - item[0]] + item[1];
            dp[i][j] = mmax(p1, p2);
        }
    }

    printf("%d", dp[m][t]);
}