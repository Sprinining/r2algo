#include <stdlib.h>

int rows, columns;
int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

int mmax(int a, int b) { return a > b ? a : b; }
int** dp;
int* data;

// 从 matrix[i][j] 出发的最长递增路径
int func(int** matrix, int i, int j, int before) {
    if (i < 0 || j < 0 || i >= rows || j >= columns) return 0;
    // 严格递增
    if (matrix[i][j] <= before) return 0;
    if (dp[i][j] != -1) return dp[i][j];
    // 遍历四个方向
    int res = 0;
    for (int k = 0; k < 4; k++) {
        int new_i = i + directions[k][0];
        int new_j = j + directions[k][1];
        res = mmax(res, func(matrix, new_i, new_j, matrix[i][j]));
    }
    // 包含自身
    dp[i][j] = res + 1;
    return dp[i][j];
}

int longestIncreasingPath(int** matrix, int matrixSize, int* matrixColSize) {
    rows = matrixSize;
    columns = matrixColSize[0];
    dp = malloc(sizeof(*dp) * rows);
    data = malloc(sizeof(*data) * rows * columns);
    for (int i = 0; i < rows; i++) {
        dp[i] = data + i * columns;
        memset(dp[i], -1, sizeof(int) * columns);
    }

    int res = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            res = mmax(res, func(matrix, i, j, -1));
        }
    }
    return res;
}