#include <math.h>
#include <stdlib.h>
#include <string.h>

#define IDX(i, j, k) (i * J * K + j * K + k)

int dirs[8][2] = {{2, -1}, {2, 1}, {1, -2}, {1, 2}, {-1, -2}, {-1, 2}, {-2, -1}, {-2, 1}};
int size;
int I, J, K;
// 三维数组扁平化
double* dp;

double dfs(int k, int r, int c) {
    if (k == 0) return 1.0;
    if (dp[IDX(k, r, c)] != -1.0) return dp[IDX(k, r, c)];
    double res = 0;
    for (int i = 0; i < 8; ++i) {
        int nr = r + dirs[i][0];
        int nc = c + dirs[i][1];
        if (nr >= 0 && nr < size && nc >= 0 && nc < size) res += dfs(k - 1, nr, nc);
    }
    dp[IDX(k, r, c)] = res / 8.0;
    return dp[IDX(k, r, c)];
}

double knightProbability(int n, int k, int row, int column) {
    size = n;
    I = k + 1;
    J = n;
    K = n;
    dp = malloc(sizeof(*dp) * I * J * K);
    for (int i = 0; i < I * J * K; ++i) dp[i] = -1.0;
    return dfs(k, row, column);
}