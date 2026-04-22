#include <stdlib.h>

#define MOD 1000000007

int dirs[2][2] = {{-1, 0}, {0, -1}};
int rows, cols;

// 到 [r, c] 位置时，模 k 余 m 的路径数目
int dfs(int** grid, int k, int r, int c, int m) {
    if (r == 0 && c == 0) return grid[0][0] % k == m ? 1 : 0;
    int res = 0;
    for (int i = 0; i < 2; ++i) {
        int br = r + dirs[i][0];
        int bc = c + dirs[i][1];
        if (br < 0 || bc < 0) continue;
        // (need + grid[r][c] % k) % k = m
        int need = (m - grid[r][c] % k + k) % k;
        res = ((long long)res + dfs(grid, k, br, bc, need)) % MOD;
    }
    return res;
}

int numberOfPaths(int** grid, int gridSize, int* gridColSize, int k) {
    rows = gridSize;
    cols = gridColSize[0];
    return dfs(grid, k, rows - 1, cols - 1, 0);
}