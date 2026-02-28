#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int m1n(int a, int b) { return a > b ? b : a; }

// 插入、删除、替换的代价分别为 a、b、c
int editDistance(char* s, char* t, int a, int b, int c) {
    int len_s = strlen(s);
    int len_t = strlen(t);
    int rows = len_s + 1;
    int columns = len_t + 1;

    // dp[i][j] 表示 s 前 i 个字符变换到 t 前 j 个字符的最小编辑距离
    int** dp = malloc(sizeof(*dp) * rows);
    // dp[0][0] = 0
    int* data = calloc(rows * columns, sizeof(*data));
    for (int i = 0; i < rows; i++) dp[i] = data + i * columns;

    // 第一列，除了第一个，都需要删除 i 个
    for (int i = 1; i < rows; i++) dp[i][0] = i * b;
    // 第一行，除了第一个，都需要插入 i 个
    for (int j = 1; j < columns; j++) dp[0][j] = j * a;

    for (int i = 1; i < rows; i++) {
        for (int j = 1; j < columns; j++) {
            // 当前状态：s 长 i，t 长 j
            // 当前问题：到达 dp[i][j] 的可能有哪些
            // s[i-1] 不参与，s 前 i-1 个就可完成 j，需要删除 s[i-1]
            int p1 = dp[i - 1][j] + b;
            // s[i-1] 参与，用于替换，前提是末尾不相同
            int p2 = s[i - 1] != t[j - 1] ? dp[i - 1][j - 1] + c : 0x7fffffff;
            // s[i-1] 参与，s 前 i 个完成 j-1，然后再末尾插入一个字符
            int p3 = dp[i][j - 1] + a;
            // s[i-1] 参与，刚好等于 t[j-1]，啥也不用干
            int p4 = s[i - 1] == t[j - 1] ? dp[i - 1][j - 1] : 0x7fffffff;
            dp[i][j] = m1n(m1n(p1, p2), m1n(p3, p4));
        }
    }
    return dp[len_s][len_t];
}

int minDistance(char* word1, char* word2) { return editDistance(word1, word2, 1, 1, 1); }

/*
    如果 a + b < c 会发生什么？
        在最优解中替换操作永远不会被使用，问题退化为只允许插入和删除的最优编辑。
        编辑距离等价于：删除掉不属于最长公共子序列的字符，再插入缺失字符。
    如果替换代价为负数会发生什么？
        代码是否仍然正确，可能得到负值，但失去距离意义
*/