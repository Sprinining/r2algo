#include <stdlib.h>
#include <string.h>

int MOD = 1000000007;

int numDistinct(char* s, char* t) {
    int rows = strlen(s) + 1;
    int columns = strlen(t) + 1;

    // dp[i][j] 表示在 s 的前 i 个字符里，能组成 t 的前 j 个字符的子序列个数
    // 问题关键是 s[i] 到底用不用
    int** dp = malloc(sizeof(*dp) * rows);
    int* data = calloc(rows * columns, sizeof(*data));
    for (int i = 0; i < rows; i++) dp[i] = data + i * columns;

    // 第一列全 1，表示 t 为空串时会出现在 s 的子序列中一次
    for (int i = 0; i < rows; i++) dp[i][0] = 1;
    // 第一行除了第一个，其余为 0，表示空串 t 的子序列中不可能出现非空串 t
    for (int j = 1; j < columns; j++) dp[0][j] = 0;

    for (int i = 1; i < rows; i++) {
        for (int j = 1; j < columns; j++) {
            // 到达当前状态前的最后一步操作可能是：不用 s[i] 和用 s[i]
            // 累加这两种可能
            dp[i][j] = dp[i - 1][j];
            if (s[i - 1] == t[j - 1]) dp[i][j] = ((long long)dp[i][j] + dp[i - 1][j - 1]) % MOD;
        }
    }
    return dp[rows - 1][columns - 1];
}
/*
    为什么 dp[i][j] 不会由 dp[i][j-1] 转移得到？
        dp[i][j-1] 的意思是用 s 的前 i 个字符，组成 t 的前 j-1 个字符的方案数。它少的是 t 的一个字符。
        但我们现在要的是组成 t 的前 j 个字符，而 t 是目标串不能“少拼一个字符”然后凭空变出来。
        在这个问题里 s 是资源池（可选），t 是目标（必须完整匹配），
        可以选择“要不要用 s[i]”，但不能选择“要不要拼 t[j]”，t 是固定必须拼完的。
*/