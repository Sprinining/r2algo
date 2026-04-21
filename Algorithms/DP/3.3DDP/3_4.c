#include <stdlib.h>

#define IDX(i, j, k) ((i) * (J) * (K) + (j) * (K) + (k))

int dirs[8][2] = {{2, -1}, {2, 1}, {1, -2}, {1, 2}, {-1, -2}, {-1, 2}, {-2, -1}, {-2, 1}};
int size;
int I, J, K;
// 三维数组扁平化
double* dp;

double knightProbability(int n, int k, int row, int column) {
    size = n;
    I = k + 1;
    J = n;
    K = n;
    // 前缀 dp
    // dp[i][r][c] = 从 [r, c] 坐标开始走 i 步仍在棋盘上的概率
    dp = malloc(sizeof(*dp) * I * J * K);

    for (int r = 0; r < J; ++r)
        for (int c = 0; c < K; ++c) dp[IDX(0, r, c)] = 1.0;

    for (int i = 1; i < I; ++i) {
        for (int r = 0; r < J; ++r) {
            for (int c = 0; c < K; ++c) {
                dp[IDX(i, r, c)] = 0.0;
                for (int index = 0; index < 8; ++index) {
                    int br = r - dirs[index][0];
                    int bc = c - dirs[index][1];
                    if (br >= 0 && br < J && bc >= 0 && bc < K)
                        dp[IDX(i, r, c)] += dp[IDX(i - 1, br, bc)];
                }
                dp[IDX(i, r, c)] /= 8.0;
            }
        }
    }

    return dp[IDX(k, row, column)];
}