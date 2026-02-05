#include <stdlib.h>

// 严格位置依赖
int minPathSum(int** grid, int gridSize, int* gridColSize) {
    int row = gridSize;
    int column = gridColSize[0];
    int** dp = (int**)malloc(sizeof(int*) * row);
    for (int i = 0; i < row; i++) {
        dp[i] = (int*)malloc(sizeof(int) * column);
    }
    for (int i = 0, temp = 0; i < row; i++) {
        temp += grid[i][0];
        dp[i][0] = temp;
    }
    for (int j = 0, temp = 0; j < column; j++) {
        temp += grid[0][j];
        dp[0][j] = temp;
    }

    for (int i = 1; i < row; i++) {
        for (int j = 1; j < column; j++) {
            if (dp[i - 1][j] < dp[i][j - 1]) {
                dp[i][j] = dp[i - 1][j] + grid[i][j];
            } else {
                dp[i][j] = dp[i][j - 1] + grid[i][j];
            }
        }
    }

    return dp[row - 1][column - 1];
}