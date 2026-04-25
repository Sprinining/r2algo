#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MMIN(a, b) ((a) > (b) ? (b) : (a))

int dfs(char *s, int l, int r) {
    if (l > r) return 0;
    if (l == r) return 1;
    int res = 0x7fffffff;
    if ((s[l] == '(' && s[r] == ')') || (s[l] == '[' && s[r] == ']')) res = dfs(s, l + 1, r - 1);
    for (int m = l; m < r; ++m) {
        res = MMIN(res, dfs(s, l, m) + dfs(s, m + 1, r));
    }
    return res;
}

int main() {
    char *s = malloc(sizeof(*s) * 101);
    scanf("%s", s);
    printf("%d", dfs(s, 0, strlen(s) - 1));
}
