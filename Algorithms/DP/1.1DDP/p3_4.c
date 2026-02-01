// https://leetcode.cn/problems/decode-ways/description/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
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

int numDecodings(char* s) {
    if (s[0] == '0') return 0;
    int n = strlen(s);

    int left, mid, right;

    left = isLegal(s, 0, 1) ? 1 : 0;
    if (n == 1) return left;

    if (isLegal(s, 1, 2)) {
        if (!isLegal(s, 1, 1))
            mid = 1;
        else
            mid = 2;
    } else {
        if (!isLegal(s, 1, 1))
            mid = 0;
        else
            mid = 1;
    }

    for (int i = 2; i < n; i++) {
        if (isLegal(s, i, 1)) {
            // 末尾单字符是合法编码
            if (!isLegal(s, i, 2)) {
                // 但最后两个字符不能组成合法编码，那这两个字符必须分割开，返回子问题
                right = mid;
            } else {
                right = mid + left;
            }
        } else {
            // 末尾单字符不是合法编码
            if (!isLegal(s, i, 2)) {
                // 如果最后两个字符也不能组成合法编码，那整个字符串就无法解码
                right = 0;
            } else {
                // 如果最后两个字符能组成合法编码，那这两个字符就不可分割，返回子问题
                right = left;
            }
        }
        left = mid;
        mid = right;
    }
    return mid;
}