int rowSize;
int columnSize;
int directions[4][2] = { {-1, 0},
                        {1,  0},
                        {0,  -1},
                        {0,  1}};

bool isPositionLegal(int i, int j) {
    return i >= 0 && i < rowSize && j >= 0 && j < columnSize;
}

// 从matrix[i, j]出发，能走出来的最长递增路径长度
int recursive(int **matrix, int i, int j, int pre) {
    if (pre >= matrix[i][j]) return 0;
    // 比pre更大（不会走回头路）
    int max = 0;
    for (int k = 0; k < 4; ++k) {
        int nextI = i + directions[k][0];
        int nextJ = j + directions[k][1];
        // 没越界
        if (isPositionLegal(nextI, nextJ)) {
            int temp = recursive(matrix, nextI, nextJ, matrix[i][j]);
            if (temp > max) max = temp;
        }
    }
    return max + 1;
}

// 暴力超时
int longestIncreasingPath(int **matrix, int matrixSize, int *matrixColSize) {
    rowSize = matrixSize;
    columnSize = *matrixColSize;
    int res = 0;
    for (int i = 0; i < rowSize; ++i) {
        for (int j = 0; j < columnSize; ++j) {
            int temp = recursive(matrix, i, j, -1);
            if (temp > res) res = temp;
        }
    }
    return res;
}