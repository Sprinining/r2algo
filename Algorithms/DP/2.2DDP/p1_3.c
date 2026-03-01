#include <stdlib.h>

int m1n(int a, int b) { return a > b ? b : a; }

// 严格位置依赖
int minPathSum(int** grid, int gridSize, int* gridColSize) {
    int row = gridSize;
    int column = gridColSize[0];
    // dp[i][j] 表示到达 grid[i][j] 所需要的最小路径和
    int** dp = malloc(sizeof(*dp) * row);
    int* data = malloc(sizeof(*data) * row * column);
    for (int i = 0; i < row; i++) dp[i] = data + i * column;
    for (int i = 0, temp = 0; i < row; i++) {
        temp += grid[i][0];
        dp[i][0] = temp;
    }
    for (int j = 0, temp = 0; j < column; j++) {
        temp += grid[0][j];
        dp[0][j] = temp;
    }

    for (int i = 1; i < row; i++)
        for (int j = 1; j < column; j++) 
            dp[i][j] = m1n(dp[i - 1][j], dp[i][j - 1]) + grid[i][j];

    return dp[row - 1][column - 1];
}