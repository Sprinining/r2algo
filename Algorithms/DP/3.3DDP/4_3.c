#include <stdlib.h>
#include <string.h>

#define MOD 1000000007
#define IDX(i, j, k) ((i) * (J) * (K) + (j) * (K) + (k))

int dirs[2][2] = {{-1, 0}, {0, -1}};
int rows, cols;
int I, J, K;
// dp[r][c][m] = 到 [r, c] 位置时，模 k 余 m 的路径数目
// 每一阶段依赖于上方和左侧格子，所以行列放在前面
int* dp;

int numberOfPaths(int** grid, int gridSize, int* gridColSize, int k) {
    rows = gridSize;
    cols = gridColSize[0];
    I = rows;
    J = cols;
    K = k;
    dp = calloc(I * J * K, sizeof(*dp));

    // 给起点状态赋值
    dp[IDX(0, 0, grid[0][0] % k)] = 1;
    for (int r = 1; r < rows; ++r) {
        for (int m = 0; m < k; ++m) {
            int need = (m - grid[r][0] % k + k) % k;
            dp[IDX(r, 0, m)] = ((long long)dp[IDX(r, 0, m)] + dp[IDX(r - 1, 0, need)]) % MOD;
        }
    }
    for (int c = 1; c < cols; ++c) {
        for (int m = 0; m < k; ++m) {
            int need = (m - grid[0][c] % k + k) % k;
            dp[IDX(0, c, m)] = ((long long)dp[IDX(0, c, m)] + dp[IDX(0, c - 1, need)]) % MOD;
        }
    }

    for (int r = 1; r < rows; ++r) {
        for (int c = 1; c < cols; ++c) {
            for (int m = 0; m < k; ++m) {
                int need = (m - grid[r][c] % k + k) % k;
                for (int i = 0; i < 2; ++i) {
                    int br = r + dirs[i][0];
                    int bc = c + dirs[i][1];
                    dp[IDX(r, c, m)] = ((long long)dp[IDX(r, c, m)] + dp[IDX(br, bc, need)]) % MOD;
                }
            }
        }
    }

    return dp[IDX(rows - 1, cols - 1, 0)];
}