#include <stdio.h>
#include <string.h>

int mmax(int a, int b) { return a > b ? a : b; }

// 返回 s[left, right] 的最长回文子序列
int func(char* s, int left, int right) {
    if (left > right) return 0;
    if (left == right) return 1;
    // 由 s[left+1, right-1] 得到，与两端字符无关
    int p1 = func(s, left + 1, right - 1);
    // 与其中一端的字符有关
    int p2 = func(s, left + 1, right);
    int p3 = func(s, left, right - 1);
    // 两端相对
    int p4 = s[left] == s[right] ? p1 + 2 : 0;
    return mmax(mmax(p1, p2), mmax(p3, p4));
}

int longestPalindromeSubseq(char* s) {
    int len = strlen(s);
    return func(s, 0, len - 1);
}