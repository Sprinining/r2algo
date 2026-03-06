#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

char *s, *p;
int len_s, len_p;

bool dfs(int i, int j) {
    // 模式串消耗完
    if (j == len_p) return i == len_s;

    // 当前位置是否是 *
    if (p[j] == '*') {
        // * 匹配 0 个
        bool p1 = dfs(i, j + 1);
        // * 匹配多个
        bool p2 = (i < len_s) && dfs(i + 1, j);
        return p1 || p2;
    } else {
        // 当前位置是否匹配
        bool first_match = (i < len_s) && (p[j] == s[i] || p[j] == '?');
        return first_match && dfs(i + 1, j + 1);
    }
}

bool isMatch(char* ss, char* pp) {
    s = ss;
    p = pp;
    len_s = strlen(s);
    len_p = strlen(p);
    return dfs(0, 0);
}