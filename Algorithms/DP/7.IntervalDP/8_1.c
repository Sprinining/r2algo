#include <stdlib.h>
#include <string.h>

#define MMIN(a, b) ((a) > (b) ? (b) : (a))

int dfs(char* s, int l, int r) {
    if (l == r) return 1;
    if (s[l] == s[r]) return dfs(s, l, r - 1);
    int res = 0x7fffffff;
    for (int m = l; m < r; ++m) {
        res = MMIN(res, dfs(s, l, m) + dfs(s, m + 1, r));
    }
    return res;
}

int strangePrinter(char* s) { return dfs(s, 0, strlen(s) - 1); }
