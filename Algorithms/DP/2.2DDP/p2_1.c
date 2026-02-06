#include <stdlib.h>
#include <string.h>

int mmax(int a, int b) { return a > b ? a : b; }

// 返回 s1[0...i] s2[0...j] 的最长公共子序列
int func(char* s1, char* s2, int i, int j) {
    if (i < 0 || j < 0) return 0;
    // 四种情况不重不漏
    // 最长公共子序列并没有包含两个末尾字符
    int p1 = func(s1, s2, i - 1, j - 1);
    // 包含了其中一个
    int p2 = func(s1, s2, i - 1, j);
    int p3 = func(s1, s2, i, j - 1);
    // 两个都包含了
    int p4 = s1[i] == s2[j] ? p1 + 1 : 0;
    return mmax(mmax(p1, p2), mmax(p3, p4));
}

int longestCommonSubsequence(char* text1, char* text2) {
    return func(text1, text2, strlen(text1) - 1, strlen(text2) - 1);
}