#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int longestValidParentheses(char* s) {
    int len = strlen(s);
    if (len < 2) return 0;

    int max = 0;
    // dp[i] 返回字符串长度为 i 且必须以末尾元素结尾的最长有效括号子串的长度
    int* dp = (int*)malloc(sizeof(int) * (len + 1));
    dp[0] = 0;
    dp[1] = 0;
    for (int i = 2; i <= len; i++) {
        if (s[i - 1] == '(') {
            dp[i] = 0;
        } else {
            // 上一个有效串的前一个位置
            int index = i - 2 - dp[i - 1];
            if (index >= 0) {
                if (s[index] == '(') {
                    dp[i] = dp[i - 1] + 2;
                    if (index >= 1) dp[i] += dp[index];
                } else {
                    dp[i] = 0;
                }
            } else {
                dp[i] = 0;
            }
        }
        if (dp[i] > max) max = dp[i];
    }
    // 最终返回 dp 数组中最大的
    return max;
}