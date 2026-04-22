#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define IDX(i, j, k) ((i) * (J) * (K) + (j) * (K) + (k))

char *s1, *s2;
int cnt[26];
int I, J, K;
// -1: 没填过 0: false 1: true
int* dp;

// 判断同种字符个数是否一样
bool same(int l1, int l2, int len) {
    memset(cnt, 0, sizeof(*cnt) * 26);
    for (int i = 0; i < len; ++i) {
        ++cnt[s1[l1 + i] - 'a'];
        --cnt[s2[l2 + i] - 'a'];
    }
    for (int i = 0; i < 26; ++i)
        if (cnt[i] != 0) return false;
    return true;
}

bool dfs(int l1, int l2, int len) {
    if (len == 1) return s1[l1] == s2[l2];
    if (dp[IDX(l1, l2, len)] != -1) return dp[IDX(l1, l2, len)] == 1;
    // 剪枝
    if (!same(l1, l2, len)) {
        dp[IDX(l1, l2, len)] = 0;
        return false;
    }
    for (int i = 1; i < len; ++i) {
        if (dfs(l1, l2, i) && dfs(l1 + i, l2 + i, len - i)) {
            dp[IDX(l1, l2, len)] = 1;
            return true;
        }
    }
    for (int i = 1; i < len; ++i) {
        if (dfs(l1, l2 + len - i, i) && dfs(l1 + i, l2, len - i)) {
            dp[IDX(l1, l2, len)] = 1;
            return true;
        }
    }
    dp[IDX(l1, l2, len)] = 0;
    return false;
}

bool isScramble(char* str1, char* str2) {
    s1 = str1;
    s2 = str2;
    I = strlen(s1);
    J = I;
    K = I + 1;
    dp = malloc(sizeof(*dp) * I * J * K);
    memset(dp, -1, sizeof(*dp) * I * J * K);
    return dfs(0, 0, strlen(s1));
}
