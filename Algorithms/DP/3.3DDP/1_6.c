#include <stdlib.h>
#include <string.h>

#define MMAX(a, b) ((a) > (b) ? (a) : (b))

// 记录每个字符串 0 和 1 的个数
int (*cnts)[2];
int** dp;
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
    // 空间压缩
    dp = malloc(sizeof(*dp) * rows * cols);
    data = calloc(rows * cols, sizeof(*data));
    for (int i = 0; i < rows; ++i) dp[i] = data + i * cols;

    for (int i = 1; i < layers; ++i) {
        int z = cnts[i - 1][0];
        int o = cnts[i - 1][1];
        for (int j = m; j >= 0; --j) {
            for (int k = n; k >= 0; --k) {
                if (z <= j && o <= k) dp[j][k] = MMAX(dp[j][k], dp[j - z][k - o] + 1);
            }
        }
    }

    return dp[m][n];
}