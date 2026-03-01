#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

bool isInterleave(char* s1, char* s2, char* s3) {
    int len_s1 = strlen(s1);
    int len_s2 = strlen(s2);
    int len_s3 = strlen(s3);
    if (len_s1 + len_s2 != len_s3) return false;
    int rows = len_s1 + 1;
    int columns = len_s2 + 1;

    // dp[i][j] 表示 s1 前 i 个字符和 s2 前 j 个字符能否拼接成 s3 前 i+j 个字符
    bool** dp = malloc(sizeof(*dp) * rows);
    bool* data = calloc(rows * columns, sizeof(*data));
    for (int i = 0; i < rows; i++) dp[i] = data + i * columns;

    dp[0][0] = true;
    // 第一行表示全都由 s2 提供字符进行拼接
    for (int j = 1; j < columns; j++) dp[0][j] = dp[0][j - 1] && (s2[j - 1] == s3[j - 1]);
    // 第一列表示全都由 s1 提供字符进行拼接
    for (int i = 1; i < rows; i++) dp[i][0] = dp[i - 1][0] && (s1[i - 1] == s3[i - 1]);

    // 当前状态是 dp[i][j]，之前的最后一步只有两个可能：最后一个字符来自 s1 或 s2
    // 所以只和上方和左侧位置有关
    for (int i = 1; i < rows; i++) {
        for (int j = 1; j < columns; j++) {
            dp[i][j] = (dp[i - 1][j] && s1[i - 1] == s3[i + j - 1]) ||
                       (dp[i][j - 1] && s2[j - 1] == s3[i + j - 1]);
        }
    }

    return dp[len_s1][len_s2];
}