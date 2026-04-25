#include <stdlib.h>
#include <string.h>

int dfs(char* s, int l, int r, int result) {
    if (l == r) return s[l] - '0' == result ? 1 : 0;
    int res = 0;
    for (int i = l + 1; i < r; i += 2) {
        int l0 = dfs(s, l, i - 1, 0);
        int l1 = dfs(s, l, i - 1, 1);
        int r0 = dfs(s, i + 1, r, 0);
        int r1 = dfs(s, i + 1, r, 1);
        if (s[i] == '&') {
            if (result == 1) {
                res += l1 * r1;
            } else {
                res += l0 * r0 + l0 * r1 + l1 * r0;
            }
        } else if (s[i] == '|') {
            if (result == 1) {
                res += l1 * r1 + l1 * r0 + l0 * r1;
            } else {
                res += l0 * r0;
            }
        } else if (s[i] == '^') {
            if (result == 1) {
                res += l1 * r0 + l0 * r1;
            } else {
                res += l0 * r0 + l1 * r1;
            }
        }
    }
    return res;
}

int countEval(char* s, int result) { return dfs(s, 0, strlen(s) - 1, result); }
