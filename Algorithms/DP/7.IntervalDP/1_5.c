#include <stdlib.h>
#include <string.h>

#define MMIN(a, b) ((a) > (b) ? (b) : (a))

int minInsertions(char* s) {
    int n = strlen(s);
    int* dp = calloc(n, sizeof(*dp));

    // 依赖于左侧，下方，左下方的格子
    // 从下往上，从左往右填
    for (int i = n - 2; i >= 0; --i) {
        int bottom_left = dp[i];
        for (int j = i + 1; j < n; ++j) {
            int down = dp[j];
            if (s[i] == s[j]) {
                dp[j] = bottom_left;
            } else {
                dp[j] = MMIN(down, dp[j - 1]) + 1;
            }
            bottom_left = down;
        }
    }

    return dp[n - 1];
}
