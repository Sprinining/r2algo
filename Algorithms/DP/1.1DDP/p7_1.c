#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int* dp;

// 必须以 i 位置结尾的最长有效括号子串的长度
int maxLen(char* s, int i) {
    int res = 0;
    if (s[i] == '(') return 0;
    // 右括号的个数
    int right = 0;
    // 右括号累计了几个
    int right_count = 0;
    while (i >= 0) {
        if (s[i] == ')') {
            right++;
            right_count++;
        } else {
            if (right > 0) {
                right--;
                if (right == 0) {
                    res += 2 * right_count;
                    right_count = 0;
                }
            } else {
                break;
            }
        }
        i--;
    }
    return res;
}

// 返回长度为 n 的字符串的最长有效括号子串的长度
int func(char* s, int n) {
    if (dp[n] != -1) return dp[n];
    if (n <= 1) {
        dp[n] = 0;
        return 0;
    }
    // 情况 1：当末尾增加的字符为 '(' 时，并不能增加最长有效括号子串的长度
    if (s[n - 1] == '(') {
        dp[n] = func(s, n - 1);
        return dp[n];
    }

    // 情况 2：当末尾增加的字符为 ')' 时
    // 新增的这个 ')' 有可能会和之前的末尾子串拼接在一起，形成一个有效括号子串
    // 情况 2.1：形成不了，或者形成了也没有之前的长度长
    dp[n] = func(s, n - 1);
    // 情况 2.2：能形成
    // 从末尾往前找，看看以末尾 ')' 为最后字符的有效括号子串的最大长度
    int max = maxLen(s, n - 1);
    if (max > dp[n]) dp[n] = max;
    return dp[n];
}

int longestValidParentheses(char* s) {
    int len = strlen(s);
    if (len == 0) return 0;
    dp = (int*)malloc(sizeof(int) * (len + 1));
    memset(dp, -1, sizeof(int) * (len + 1));
    return func(s, len);
}