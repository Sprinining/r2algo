#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

char *s, *p;
int len_s, len_p;

// 返回 s[i:] 和 p[j:] 是否匹配
bool dfs(int i, int j) {
    // 1. 模式串消耗完，只有当字符串也结束才算匹配成功
    if (j == len_p) return i == len_s;

    // 2. 当前字符是否匹配
    bool first_match = (i < len_s) && (s[i] == p[j] || p[j] == '.');

    // 3. 判断模式串下一个字符是不是 *
    if (j + 1 < len_p && p[j + 1] == '*') {
        // * 匹配 0 次，跳过 p[j] 和 *
        bool p1 = dfs(i, j + 2);
        // * 匹配多次，前提是当前字符能匹配
        bool p2 = first_match && dfs(i + 1, j);
        return p1 || p2;
    } else {
        // 4. 普通字符匹配
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
