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
    // 隐式逆拓扑序
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

// O(mn)
// 时间复杂度取决于“每个状态算几次”，记忆化搜索版本每个格子只会真正计算一次
int longestIncreasingPath(int** matrix, int matrixSize, int* matrixColSize) {
    rows = matrixSize;
    columns = matrixColSize[0];
    dp = malloc(sizeof(*dp) * rows);
    data = malloc(sizeof(*data) * rows * columns);
    for (int i = 0; i < rows; i++) {
        dp[i] = data + i * columns;
        memset(dp[i], -1, sizeof(*dp[i]) * columns);
    }

    int res = 0;
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < columns; j++) res = mmax(res, func(matrix, i, j, -1));
    return res;
}
/*
    二维 DP 压缩的前提是状态具有“单调的遍历顺序”，即每个状态只依赖按固定顺序已经计算过的状态。
    而本题中，dp[i][j] 依赖所有比 matrix[i][j] 大的相邻格子，状态顺序由数值大小决定，
    而不是由 i,j 顺序决定，因此普通二维压缩不成立。
*/
/*
    DFS 递归版本则是隐式逆拓扑序：回溯时先计算更大的格子，再计算当前格子。
    排序法显式构造逆拓扑序：先把所有格子拉平成数组，按数值从大到小排序，然后迭代更新 dp。
    两者本质都是保证在计算 dp[i][j] 时，所有依赖的更大邻居已经计算完成。
*/