#include <stdlib.h>
#include <string.h>

int MOD = 1000000007;

int numDistinct(char* s, char* t) {
    int len_s = strlen(s);
    int len_t = strlen(t);
    int rows = len_s + 1;
    int columns = len_t + 1;

    // dp[i][j] 表示在 s 的前 i 个字符里，能组成 t 的前 j 个字符的子序列个数
    // 问题关键是 s[i] 到底用不用
    int** dp = (int**)malloc(sizeof(int*) * rows);
    for (int i = 0; i < rows; i++) {
        dp[i] = (int*)malloc(sizeof(int) * columns);
        memset(dp[i], 0, sizeof(int) * columns);
    }

    // 第一列全 1，表示 t 为空串时会出现在 s 的子序列中一次
    for (int i = 0; i < rows; i++) dp[i][0] = 1;
    // 第一行除了第一个，其余为 0，表示空串 t 的子序列中不可能出现非空串 t
    for (int j = 1; j < columns; j++) dp[0][j] = 0;

    for (int i = 1; i < rows; i++) {
        for (int j = 1; j < columns; j++) {
            if (s[i - 1] != t[j - 1]) {
                // 情况 1：根本不能用 s[i]，问题等价于在 s 的前 i-1 个字符里，拼 t 的前 j 个字符
                dp[i][j] = dp[i - 1][j];
            } else {
                // 情况 2：可以用 s[i]，但前提是 s[i-1] == t[j-1]，前面必须已经匹配好 t 的前 j-1 个字符
                // 结果要把选和不选的可能累计起来
                dp[i][j] = ((long long)dp[i - 1][j] + dp[i - 1][j - 1]) % MOD;
            }
        }
    }

    return dp[len_s][len_t];
}
/*
    为什么不是 dp[i][j-1]？
        dp[i][j-1] 是用 s 前 i 个字符拼 t 前 j-1 个字符，现在目标是拼 t 的前 j 个字符，少一个字符不等价
        而我们只是在决定：当前 s[i-1] 用还是不用，所以只会从：s 少一个字符（i-1）转移过来
*/