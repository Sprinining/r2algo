#include <stdlib.h>

int row;
int column;
int** dp;

// 记忆化搜索
// 到达 grid[i][j] 所需要的最小路径和
int func(int** grid, int i, int j) {
    if (dp[i][j] != -1) return dp[i][j];
    if (i == 0 && j == 0) {
        dp[i][j] = grid[0][0];
    } else {
        int left = 0x7fffffff;
        int up = 0x7fffffff;
        if (j > 0) left = func(grid, i, j - 1);
        if (i > 0) up = func(grid, i - 1, j);
        dp[i][j] = (left < up ? left : up) + grid[i][j];
    }
    return dp[i][j];
}

int minPathSum(int** grid, int gridSize, int* gridColSize) {
    row = gridSize;
    column = gridColSize[0];
    dp = (int**)malloc(sizeof(int*) * row);
    for (int i = 0; i < row; i++) {
        dp[i] = (int*)malloc(sizeof(int) * column);
        memset(dp[i], -1, sizeof(int) * column);
    }

    return func(grid, row - 1, column - 1);
}