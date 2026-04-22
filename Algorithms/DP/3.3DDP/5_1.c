#include <stdbool.h>
#include <stdlib.h>

char *s1, *s2;

bool dfs(int l1, int r1, int l2, int r2) {
    if (l1 == r1) return s1[l1] == s2[l2];
    // 左右两部分等长
    // s1[l1, i][i+1, r1]
    // s2[l2, j][j+1, r2]
    for (int i = l1, j = l2; i < r1; ++i, ++j) {
        if (dfs(l1, i, l2, j) && dfs(i + 1, r1, j + 1, r2)) return true;
    }
    // s1 左等于 s2 右
    // s1[l1, i][i+1, r1]
    // s2[l2, j-1][j, r2]
    for (int i = l1, j = r2; i < r1; ++i, --j) {
        if (dfs(l1, i, j, r2) && dfs(i + 1, r1, l2, j - 1)) return true;
    }
    return false;
}

bool isScramble(char* str1, char* str2) {
    s1 = str1;
    s2 = str2;
    return dfs(0, strlen(s1) - 1, 0, strlen(s2) - 1);
}