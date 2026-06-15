#include <string.h>

#define MMAX(a, b) ((a) > (b) ? (a) : (b))

int cnt[128];
int kind;

int lengthOfLongestSubstring(char* s) {
    memset(cnt, 0, sizeof(cnt));
    kind = 0;
    int n = strlen(s);

    int res = 0;
    // 只在循环结束自增 r
    // 循环内部自增 l 去重
    for (int l = 0, r = 0; r < n; ++r) {
        ++cnt[s[r]];
        if (cnt[s[r]] == 1) ++kind;

        while (kind != r - l + 1) {
            --cnt[s[l]];
            if (cnt[s[l]] == 0) --kind;
            ++l;
        }
        res = MMAX(res, kind);
    }

    return res;
}
