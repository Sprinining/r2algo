#include <string.h>

int* dp;

// 返回 s[0...n] 的解码总数
int func(char* s, int n) {
    // 两种基线条件
    if (n < 0) return 1;
    if (n == 0) return s[0] != '0' ? 1 : 0;

    if (dp[n] != -1) return dp[n];

    int val = (s[n - 1] - '0') * 10 + (s[n] - '0');
    if (val == 0 || (val > 26 && (val % 10 == 0))) {
        // 非法编码：00,30,40,50...
        dp[n] = 0;
    } else if (val == 10 || val == 20) {
        // 两个字符不可分割：10,20
        dp[n] = func(s, n - 2);
    } else if ((val >= 1 && val <= 9) || (val > 26 && (val % 10) != 0)) {
        // 两个字符必须分割
        dp[n] = func(s, n - 1);
    } else if ((val >= 11 && val <= 19) || (val >= 21 && val <= 26)) {
        // 可以分割
        dp[n] = func(s, n - 1) + func(s, n - 2);
    }

    return dp[n];
}

int numDecodings(char* s) {
    if (s[0] == '0') return 0;
    int len = strlen(s);
    dp = (int*)malloc(sizeof(int) * len);
    memset(dp, -1, sizeof(int) * len);
    return func(s, len - 1);
}