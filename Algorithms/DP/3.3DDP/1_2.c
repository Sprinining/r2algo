#include <stdlib.h>
#include <string.h>

#define MMAX(a, b) ((a) > (b) ? (a) : (b))

// 记录每个字符串 0 和 1 的个数
int (*cnts)[2];
// **错误但被代码实现出来的含义：dp[index][m][n] =
// 在“某一条 DFS 路径的当前 len 状态”下，从 index 开始能得到的最大结果
int*** dp;
int** plane;
int* data;

// **错误解法：把 len 当作状态的一部分，但 dp 没有记录它
// dp 认为“同一个状态”是 (index, m, n)，而真实状态是 (index, m, n, len)
// 同一个 (index, m, n) 被不同路径到达，但 len 不同
int dfs(int strsSize, int m, int n, int index, int len) {
    if (index == strsSize) return len;
    if (dp[index][m][n] != -1) return dp[index][m][n];
    // 不选
    // **当前已经选了多少个（len），混进了 dp 状态
    int p1 = dfs(strsSize, m, n, index + 1, len);
    // 选
    int z = cnts[index][0];
    int o = cnts[index][1];
    int p2 = (z <= m && o <= n) ? dfs(strsSize, m - z, n - o, index + 1, len + 1) : 0;
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

    return dfs(strsSize, m, n, 0, 0);
}