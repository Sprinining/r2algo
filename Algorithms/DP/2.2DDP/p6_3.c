#include <stdlib.h>
#include <string.h>

int MOD = 1000000007;

// 空间优化
int numDistinct(char* s, char* t) {
    int rows = strlen(s) + 1;
    int columns = strlen(t) + 1;

    int* dp = calloc(columns, sizeof(*dp));
    dp[0] = 1;

    // 当前位置只依赖于上方和左上方
    for (int i = 1; i < rows; i++) {
        // 所以每行可以从右往左填
        for (int j = columns - 1; j > 0; j--) {
            if (s[i - 1] == t[j - 1]) {
                dp[j] = ((long long)dp[j] + dp[j - 1]) % MOD;
            }
        }
    }

    return dp[columns - 1];
}