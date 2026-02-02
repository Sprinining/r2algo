#include <stdlib.h>
#include <string.h>

int MOD = 1e9 + 7;

// 空间压缩
// 返回长度为 n 的字符串的编码方法总数
int numDecodings(char* s) {
    if (s[0] == '0') return 0;

    int len = strlen(s);
    long long left, mid, right;
    left = 1;
    mid = (s[0] == '*') ? 9 : 1;

    for (int i = 2; i <= len; i++) {
        // 最后两个字符
        char a = s[i - 2];
        char b = s[i - 1];
        long long sum = 0;
        // 单字符解码
        if (b == '*') {
            sum = (sum + mid * 9) % MOD;
        } else if (b != '0') {
            sum = (sum + mid) % MOD;
        }
        // 双字符解码
        if (a != '*' && b != '*') {
            int val = (a - '0') * 10 + (b - '0');
            if (val >= 10 && val <= 26) sum = (sum + left) % MOD;
        } else if (a != '*' && b == '*') {
            if (a == '1') {
                // b 从 1 到 9 都符合
                sum = (sum + left * 9) % MOD;
            } else if (a == '2') {
                // b 从 1 到 6 符合
                sum = (sum + left * 6) % MOD;
            }
            // a == 0 || a > 2 时，无法双字符解码
        } else if (a == '*' && b != '*') {
            if (b >= '0' && b <= '6') {
                // a 为 1 或 2
                sum = (sum + left * 2) % MOD;
            } else {
                // a 只能为 1
                sum = (sum + left * 1) % MOD;
            }
        } else if (a == '*' && b == '*') {
            // 11~19,21~26 共 15 种
            sum = (sum + left * 15) % MOD;
        }
        right = sum;
        left = mid;
        mid = right;
    }

    return (int)mid;
}