#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 自底向上严格位置依赖
// dp[n] 含义由 s[0...n] 的解码方法改为长度为 n 的字符串的解码方法
int numDecodings(char* s) {
    // 首先排除前导零
    if (s[0] == '0') return 0;
    int len = strlen(s);
    // 只有一个字符
    if (len == 1) return 1;

    // 两个及以上
    int* dp = (int*)malloc(sizeof(int) * (len + 1));
    // 避免讨论长度为 2 的字符串的情况
    dp[0] = 1;
    dp[1] = 1;

    for (int i = 2; i <= len; i++) {
        int val = (s[i - 2] - '0') * 10 + (s[i - 1] - '0');
        if (val == 0 || (val > 26 && (val % 10 == 0))) {
            // 非法编码：00,30,40,50...
            dp[i] = 0;
        } else if (val == 10 || val == 20) {
            // 两个字符不可分割：10,20
            dp[i] = dp[i - 2];
        } else if ((val >= 1 && val <= 9) || (val > 26 && (val % 10) != 0)) {
            // 两个字符必须分割
            dp[i] = dp[i - 1];
        } else if ((val >= 11 && val <= 19) || (val >= 21 && val <= 26)) {
            // 可以分割
            dp[i] = dp[i - 1] + dp[i - 2];
        }
    }

    return dp[len];
}