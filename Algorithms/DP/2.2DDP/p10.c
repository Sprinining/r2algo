// 删除至少几个字符可以变成另一个字符串的子串
// 给定两个字符串 s 和 t
// 返回 s 至少删除多少字符可以成为 t 的子串
// s 长度 <=20, t 长度 <=20
// 对数器验证

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int m1n(int a, int b) { return a > b ? b : a; }

// 暴力判断 sub 是不是 str 的子串
bool isSubStr(char* sub, char* str) {
    int len_sub = strlen(sub);
    int len_str = strlen(str);
    if (len_sub > len_str) return false;
    for (int i = 0; i <= len_str - len_sub; i++) {
        int j = 0;
        while (j < len_sub && (sub[j] == str[i + j])) j++;
        if (j == len_sub) return true;
    }
    return false;
}

// 暴力递归
int minDeleteToSubStr1(char* s, char* t) {
    int len_s = strlen(s);
    int res = 0x7fffffff;
    // 子序列共有 2 ^ (len_s) 种可能
    for (int mask = 0; mask < (1 << len_s); mask++) {
        // 待生成的子序列字符串
        char sub[21];
        int idx = 0;
        // 根据位掩码生成 s 的子序列
        for (int j = 0; j < len_s; j++) {
            if ((mask & (1 << j)) != 0) sub[idx++] = s[j];
        }
        sub[idx] = '\0';
        // 判断 sub 是否是 t 的子串
        if (isSubStr(sub, t)) {
            res = m1n(res, len_s - idx);
        }
    }
    return res;
}

// DP 版本
int minDeleteToSubStr2(char* s, char* t) {
    int len_s = strlen(s);
    int len_t = strlen(t);

    // dp[i][j] 表示：s[0..i-1] 至少删除多少字符
    // 可以变成 t[0..j-1] 的某个后缀（允许匹配 t 的任意连续片段）
    int dp[21][21];             // s 和 t 都 <= 20
    memset(dp, 0, sizeof(dp));  // 初始化为 0

    // 初始化：t 前 0 个字符（空串）
    // 要让 s 的前 i 个字符变成空串，需要删除 i 个字符
    for (int i = 1; i <= len_s; i++) dp[i][0] = i;

    // DP 转移
    for (int i = 1; i <= len_s; i++) {
        for (int j = 1; j <= len_t; j++) {
            if (s[i - 1] == t[j - 1]) {
                // 如果当前字符相等，不删除，沿用前一个状态
                dp[i][j] = dp[i - 1][j - 1];
            } else {
                // 如果当前字符不等，需要删除 s[i-1]，状态加 1
                dp[i][j] = dp[i - 1][j] + 1;
            }
        }
    }

    // 最终答案：s 全部字符用完
    // t 可以匹配任意长度前缀（子串可能从 t 的任意位置开始）
    int res = 0x7fffffff;
    for (int j = 0; j <= len_t; j++) {
        res = m1n(res, dp[len_s][j]);
    }

    return res;  // 返回最少删除次数
}

// 生成随机字符串
void randomString(char* buf, int len, int v) {
    for (int i = 0; i < len; i++) {
        buf[i] = 'a' + rand() % v;
    }
    buf[len] = '\0';
}

// 对数器测试
int main() {
    srand(0);  // 固定随机种子
    int n = 12;
    int v = 3;
    int testTime = 2000;
    char s1[21], s2[21];
    printf("测试开始\n");
    for (int i = 0; i < testTime; i++) {
        int len1 = rand() % n + 1;
        int len2 = rand() % n + 1;
        randomString(s1, len1, v);
        randomString(s2, len2, v);
        int ans1 = minDeleteToSubStr1(s1, s2);
        int ans2 = minDeleteToSubStr2(s1, s2);
        if (ans1 != ans2) {
            printf("出错了!\n");
            printf("s1=%s, s2=%s, ans1=%d, ans2=%d\n", s1, s2, ans1, ans2);
            return 0;
        }
    }
    printf("测试结束\n");
    return 0;
}