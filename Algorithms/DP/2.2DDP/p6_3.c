#include <stdlib.h>
#include <string.h>

int MOD = 1000000007;

// 空间优化
int numDistinct(char* s, char* t) {
    int len_s = strlen(s);
    int len_t = strlen(t);
    int rows = len_s + 1;
    int columns = len_t + 1;

    int* dp = (int*)malloc(sizeof(int) * columns);
    memset(dp, 0, sizeof(int) * columns);
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

    return dp[len_t];
}