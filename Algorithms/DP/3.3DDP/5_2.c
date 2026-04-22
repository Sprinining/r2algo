#include <stdbool.h>
#include <stdlib.h>

char *s1, *s2;

bool dfs(int l1, int l2, int len) {
    if (len == 1) return s1[l1] == s2[l2];
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