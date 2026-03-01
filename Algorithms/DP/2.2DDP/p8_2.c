#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

// 空间压缩
bool isInterleave(char* s1, char* s2, char* s3) {
    int len_s1 = strlen(s1);
    int len_s2 = strlen(s2);
    int len_s3 = strlen(s3);
    if (len_s1 + len_s2 != len_s3) return false;
    int rows = len_s1 + 1;
    int columns = len_s2 + 1;

    bool* dp = calloc(columns, sizeof(*dp));

    dp[0] = true;
    for (int j = 1; j < columns; j++) dp[j] = dp[j - 1] && (s2[j - 1] == s3[j - 1]);

    for (int i = 1; i < rows; i++) {
        dp[0] = dp[0] && (s1[i - 1] == s3[i - 1]);
        for (int j = 1; j < columns; j++) {
            dp[j] =
                (dp[j] && s1[i - 1] == s3[i + j - 1]) || (dp[j - 1] && s2[j - 1] == s3[i + j - 1]);
        }
    }

    return dp[len_s2];
}