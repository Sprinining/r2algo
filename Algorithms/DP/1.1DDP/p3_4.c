#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 状态压缩
int numDecodings(char* s) {
    int len = strlen(s);
    // 只有一个字符
    if (len == 1) return s[0] == '0' ? 0 : 1;

    // 两个及以上
    // 首先排除前导零
    if (s[0] == '0') return 0;

    int left, mid, right;
    left = 1;
    int val = (s[0] - '0') * 10 + (s[1] - '0');
    if (val == 10 || val == 20 || (val > 26 && (val % 10) != 0)) {
        mid = 1;
    } else if ((val >= 11 && val <= 19) || (val >= 21 && val <= 26)) {
        mid = 2;
    } else {
        mid = 0;
    }

    for (int i = 2; i < len; i++) {
        int val = (s[i - 1] - '0') * 10 + (s[i] - '0');
        if (val == 0 || (val > 26 && (val % 10 == 0))) {
            // 非法编码：00,30,40,50...
            right = 0;
        } else if (val == 10 || val == 20) {
            // 两个字符不可分割：10,20
            right = left;
        } else if ((val >= 1 && val <= 9) || (val > 26 && (val % 10) != 0)) {
            // 两个字符必须分割
            right = mid;
        } else if ((val >= 11 && val <= 19) || (val >= 21 && val <= 26)) {
            // 可以分割
            right = mid + left;
        }
        left = mid;
        mid = right;
    }

    return mid;
}