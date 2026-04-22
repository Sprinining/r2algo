#include <stdlib.h>

#define MOD 1000000007

int numberOfPaths(int** grid, int gridSize, int* gridColSize, int k) {
    int rows = gridSize;
    int cols = gridColSize[0];

    int** prev = malloc(sizeof(int*) * cols);
    int* data1 = calloc(cols * k, sizeof(int));
    for (int c = 0; c < cols; c++) prev[c] = data1 + c * k;
    int** curr = malloc(sizeof(int*) * cols);
    int* data2 = calloc(cols * k, sizeof(int));
    for (int c = 0; c < cols; c++) curr[c] = data2 + c * k;

    // 起点初始化
    prev[0][grid[0][0] % k] = 1;

    // 初始化第一行
    for (int c = 1; c < cols; ++c) {
        for (int m = 0; m < k; ++m) {
            int need = (m - grid[0][c] % k + k) % k;
            prev[c][m] = prev[c - 1][need];
        }
    }

    // 逐行 DP
    for (int r = 1; r < rows; ++r) {
        // 当前行第一列
        for (int m = 0; m < k; ++m) {
            int need = (m - grid[r][0] % k + k) % k;
            curr[0][m] = prev[0][need];
        }

        // 当前行其他列
        for (int c = 1; c < cols; ++c) {
            for (int m = 0; m < k; m++) {
                int need = (m - grid[r][c] % k + k) % k;
                curr[c][m] = ((long long)prev[c][need] + curr[c - 1][need]) % MOD;
            }
        }

        int** temp = prev;
        prev = curr;
        curr = temp;
    }

    return prev[cols - 1][0] % MOD;
}