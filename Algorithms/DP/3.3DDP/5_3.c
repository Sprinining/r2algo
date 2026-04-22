#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

char *s1, *s2;
int cnt[26];

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
    // 剪枝
    if (!same(l1, l2, len)) return false;
    for (int i = 1; i < len; ++i) {
        if (dfs(l1, l2, i) && dfs(l1 + i, l2 + i, len - i)) return true;
    }
    for (int i = 1; i < len; ++i) {
        if (dfs(l1, l2 + len - i, i) && dfs(l1 + i, l2, len - i)) return true;
    }
    return false;
}

bool isScramble(char* str1, char* str2) {
    s1 = str1;
    s2 = str2;
    return dfs(0, 0, strlen(s1));
}