#include <stdlib.h>
#include <string.h>

int mmax(int a, int b) { return a > b ? a : b; }

// 每次粉碎 = 两块石头互相抵消 → 本质是把石头分成两堆，最终剩余 = 两堆重量差
// 问题转化为：找一个子集，使其总和尽量接近总和的一半
// 最小剩余重量 = sum - 2 * 子集总和
int lastStoneWeightII(int* stones, int stonesSize) {
    int sum = 0;
    for (int i = 0; i < stonesSize; ++i) sum += stones[i];
    int limit = sum / 2;
    int rows = stonesSize + 1;
    int cols = limit + 1;
    // dp[i][j] = 前 i 个石头中，尽量接近 j 的总和
    int** dp = malloc(sizeof(*dp) * rows);
    int* data = calloc(rows * cols, sizeof(*data));
    for (int i = 0; i < rows; ++i) dp[i] = data + i * cols;

    for (int i = 1; i < rows; ++i) {
        for (int j = 1; j < cols; ++j) {
            int p1 = dp[i - 1][j];
            int p2 = 0;
            if (stones[i - 1] <= j) p2 = dp[i - 1][j - stones[i - 1]] + stones[i - 1];
            dp[i][j] = mmax(p1, p2);
        }
    }
    int small = dp[rows - 1][cols - 1];
    return sum - 2 * small;
}
