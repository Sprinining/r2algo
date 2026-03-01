#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int m1n(int a, int b) { return a > b ? b : a; }

int editDistance(char* s, char* t, int a, int b, int c) {
    int rows = strlen(s) + 1;
    int columns = strlen(t) + 1;

    int* dp = calloc(columns, sizeof(dp));
    // 第一行
    for (int j = 1; j < columns; j++) dp[j] = j * a;

    // 依赖于左侧，左上方，上方三个位置
    // 由于依赖左侧，所以每一行只能从左往右填
    int top_left;
    int backup;
    for (int i = 1; i < rows; i++) {
        top_left = dp[0];
        dp[0] += b;
        for (int j = 1; j < columns; j++) {
            backup = dp[j];
            int p1 = dp[j] + b;
            int p2 = s[i - 1] != t[j - 1] ? top_left + c : 0x7fffffff;
            int p3 = dp[j - 1] + a;
            int p4 = s[i - 1] == t[j - 1] ? top_left : 0x7fffffff;
            dp[j] = m1n(m1n(p1, p2), m1n(p3, p4));
            top_left = backup;
        }
    }
    return dp[columns - 1];
}

int minDistance(char* word1, char* word2) { return editDistance(word1, word2, 1, 1, 1); }
