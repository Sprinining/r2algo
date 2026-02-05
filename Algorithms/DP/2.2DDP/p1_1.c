int row;
int column;

// 暴力递归
// 到达 grid[i][j] 所需要的最小路径和
int func(int** grid, int i, int j) {
    if (i == 0 && j == 0) return grid[0][0];
    int left = 0x7fffffff;
    int up = 0x7fffffff;
    if (j > 0) left = func(grid, i, j - 1);
    if (i > 0) up = func(grid, i - 1, j);
    return (left < up ? left : up) + grid[i][j];
}

int minPathSum(int** grid, int gridSize, int* gridColSize) {
    row = gridSize;
    column = gridColSize[0];
    return func(grid, row - 1, column - 1);
}