#include <stdlib.h>
#include <string.h>

#define MMAX(a, b) ((a) > (b) ? (a) : (b))

// 记录每个字符串 0 和 1 的个数
int (*cnts)[2];
int*** dp;
int** plane;
int* data;

// 记忆化搜索
int dfs(int strsSize, int m, int n, int index) {
    if (index == strsSize) return 0;
    if (dp[index][m][n] != -1) return dp[index][m][n];
    // 不选
    int p1 = dfs(strsSize, m, n, index + 1);
    // 选
    int z = cnts[index][0];
    int o = cnts[index][1];
    int p2 = (z <= m && o <= n) ? 1 + dfs(strsSize, m - z, n - o, index + 1) : 0;
    dp[index][m][n] = MMAX(p1, p2);
    return dp[index][m][n];
}

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

    int rows = m + 1;
    int cols = n + 1;
    // 前缀式 dp
    // dp[i][j][k] = 从第 i 个字符串开始选，在最多还能用 j 个 0、k 个 1 的限制下，最多能选多少个字符串
    dp = malloc(sizeof(*dp) * strsSize);
    plane = malloc(sizeof(*plane) * strsSize * rows);
    data = malloc(sizeof(*data) * strsSize * rows * cols);
    memset(data, -1, sizeof(*data) * strsSize * rows * cols);
    for (int i = 0; i < strsSize; ++i) {
        dp[i] = plane + i * rows;
        for (int j = 0; j < rows; ++j) {
            dp[i][j] = data + (i * rows * cols + j * cols);
        }
    }

    return dfs(strsSize, m, n, 0);
}