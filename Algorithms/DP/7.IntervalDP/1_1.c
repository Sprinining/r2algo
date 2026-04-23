#include <stdlib.h>
#include <string.h>

#define MMIN(a, b) ((a) > (b) ? (b) : (a))

int dfs(char* s, int l, int r) {
    // 单个字符回文；越界也不需要插入字符
    if (l >= r) return 0;
    // 两端字符相同时
    if (s[l] == s[r]) return dfs(s, l + 1, r - 1);
    // 两端字符不同时，两种情况，在末尾插入 s[l] 或者在开头插入 s[r]
    return MMIN(dfs(s, l, r - 1), dfs(s, l + 1, r)) + 1;
}

int minInsertions(char* s) { return dfs(s, 0, strlen(s) - 1); }