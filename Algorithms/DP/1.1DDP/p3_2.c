#include <string.h>

int* dp;

// 返回长度为 n 的字符串的解码总数
int func(char* s, int n) {
    // 两种基线条件
    if (n == 0) return 1;
    if (n == 1) return s[0] != '0' ? 1 : 0;

    if (dp[n] != -1) return dp[n];

    int sum = 0;
    // 最后的一次解码要么是单字符解码要么是双字符解码
    // 只要包含这两类就不会漏解
    // 单字符解码
    if (s[n - 1] != '0') sum += func(s, n - 1);
    // 双字符解码
    int val = (s[n - 2] - '0') * 10 + (s[n - 1] - '0');
    if (val >= 10 && val <= 26) sum += func(s, n - 2);
    dp[n] = sum;

    return dp[n];
}

int numDecodings(char* s) {
    if (s[0] == '0') return 0;
    int len = strlen(s);
    dp = (int*)malloc(sizeof(int) * (len + 1));
    memset(dp, -1, sizeof(int) * (len + 1));
    return func(s, len);
}