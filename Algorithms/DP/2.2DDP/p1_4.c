#include <stdlib.h>

// 空间压缩
int minPathSum(int** grid, int gridSize, int* gridColSize) {
    int row = gridSize;
    int column = gridColSize[0];
    int* dp = (int*)malloc(sizeof(int) * column);
    // 重复利用第一行
    dp[0] = grid[0][0];
    for (int j = 1; j < column; j++) {
        dp[j] = dp[j - 1] + grid[0][j];
    }

    for (int i = 1; i < row; i++) {
        dp[0] += grid[i][0];
        for (int j = 1; j < column; j++) {
            if (dp[j - 1] < dp[j]) dp[j] = dp[j - 1];
            dp[j] += grid[i][j];
        }
    }

    return dp[column - 1];
}