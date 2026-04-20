#include <stdlib.h>
#include <string.h>

#define MMAX(a, b) ((a) > (b) ? (a) : (b))

// 记录每个字符串 0 和 1 的个数
int (*cnts)[2];
int*** dp;
int** plane;
int* data;

int findMaxForm(char** strs, int strsSize, int m, int n) {
    cnts = malloc(sizeof(*cnts) * strsSize);
    for (int i = 0; i < strsSize; ++i) {
        int z = 0, slen = strlen(strs[i]);
        for (int j = 0; j < slen; ++j) {
            if (strs[i][j] == '0') ++z;
        }
        cnts[i][0] = z;
        cnts[i][1] = slen - z;
    }

    int layers = strsSize + 1;
    int rows = m + 1;
    int cols = n + 1;
    // 后缀式 dp
    // dp[i][j][k] = 从前 i 个字符串里选，在最多还能用 j 个 0、k 个 1 的限制下，最多能选多少个字符串
    dp = malloc(sizeof(*dp) * layers);
    plane = malloc(sizeof(*plane) * layers * rows);
    data = calloc(layers * rows * cols, sizeof(*data));
    for (int i = 0; i < layers; ++i) {
        dp[i] = plane + i * rows;
        for (int j = 0; j < rows; ++j) {
            dp[i][j] = data + (i * rows * cols + j * cols);
        }
    }

    for (int i = 1; i < layers; ++i) {
        int z = cnts[i - 1][0];
        int o = cnts[i - 1][1];
        for (int j = 0; j < rows; ++j) {
            for (int k = 0; k < cols; ++k) {
                // 不选
                dp[i][j][k] = dp[i - 1][j][k];
                // 选
                if (z <= j && o <= k) dp[i][j][k] = MMAX(dp[i][j][k], dp[i - 1][j - z][k - o] + 1);
            }
        }
    }

    return dp[strsSize][m][n];
}