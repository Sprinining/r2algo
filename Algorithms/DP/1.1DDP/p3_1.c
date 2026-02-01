// https://leetcode.cn/problems/decode-ways/description/

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

// 从 s[i] 往前 k 个字符能否组成合法的编码（包含 s[i]）
// k 只能为 1 或 2
bool isLegal(char* s, int i, int k) {
    if (k == 1 && i >= 0) {
        // 单个字符时，范围 1 ~ 9，只要不是字符 0 就是合法的
        return s[i] != '0';
    } else if (k == 2 && i >= 1) {
        // 两个字符时，范围 10 ~ 26
        int num = ((s[i - 1] - '0') * 10) + (s[i] - '0');
        if (num >= 10 && num <= 26) return true;
        return false;
    } else {
        return false;
    }
}

// 返回 s[0...n] 的解码总数
int func(char* s, int n) {
    if (n < 0) return 1;
    if (n == 0 && isLegal(s, n, 1)) return 1;
    if (isLegal(s, n, 1)) {
        // 末尾单字符是合法编码
        if (!isLegal(s, n, 2)) {
            // 但最后两个字符不能组成合法编码，那这两个字符必须分割开，返回子问题
            return func(s, n - 1);
        } else {
            return func(s, n - 1) + func(s, n - 2);
        }
    } else {
        // 末尾单字符不是合法编码
        if (!isLegal(s, n, 2)) {
            // 如果最后两个字符也不能组成合法编码，那整个字符串就无法解码
            return 0;
        } else {
            // 如果最后两个字符能组成合法编码，那这两个字符就不可分割，返回子问题
            return func(s, n - 2);
        }
    }
}

int numDecodings(char* s) {
    if (s[0] == '0') return 0;
    return func(s, strlen(s) - 1);
}