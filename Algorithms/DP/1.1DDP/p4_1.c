#include <stdlib.h>
#include <string.h>

int MOD = 1e9 + 7;

// 暴力递归
// 返回长度为 n 的字符串的编码方法总数
long long func(char* s, int n) {
    if (n == 0) return 1;
    if (n == 1) {
        if (s[0] == '*') return 9;
        return s[0] == '0' ? 0 : 1;
    }

    long long sum = 0;
    // 最后两个字符
    char a = s[n - 2];
    char b = s[n - 1];
    // 单字符解码
    if (b == '*') {
        sum = (sum + func(s, n - 1) * 9) % MOD;
    } else if (b != '0') {
        sum = (sum + func(s, n - 1)) % MOD;
    }
    // 双字符解码
    if (a != '*' && b != '*') {
        int val = (a - '0') * 10 + (b - '0');
        if (val >= 10 && val <= 26) sum = (sum + func(s, n - 2)) % MOD;
    } else if (a != '*' && b == '*') {
        if (a == '1') {
            // b 从 1 到 9 都符合
            sum = (sum + func(s, n - 2) * 9) % MOD;
        } else if (a == '2') {
            // b 从 1 到 6 符合
            sum = (sum + func(s, n - 2) * 6) % MOD;
        }
        // a == 0 || a > 2 时，无法双字符解码
    } else if (a == '*' && b != '*') {
        if (b >= '0' && b <= '6') {
            // a 为 1 或 2
            sum = (sum + func(s, n - 2) * 2) % MOD;
        } else {
            // a 只能为 1
            sum = (sum + func(s, n - 2) * 1) % MOD;
        }
    } else if (a == '*' && b == '*') {
        // 11~19,21~26 共 15 种
        sum = (sum + func(s, n - 2) * 15) % MOD;
    }

    return sum;
}

int numDecodings(char* s) {
    if (s[0] == '0') return 0;
    int len = strlen(s);
    return (int)func(s, len);
}