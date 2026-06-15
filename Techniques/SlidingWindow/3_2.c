#include <stdlib.h>
#include <string.h>

#define INF_MAX 0x3f3f3f3f

char* minWindow(char* s, char* t) {
    // 记录 t 中每种字符所需的个数
    // 负数表示缺失次数
    // 正数表示在窗口中多出现了
    int cnt[128] = {0};
    // 还差多少个字符能完全覆盖
    int missing = 0;
    for (int i = 0; t[i]; ++i) {
        --cnt[t[i]];
        ++missing;
    }

    int min_len = INF_MAX;
    int start = 0;

    for (int l = 0, r = 0; s[r]; ++r) {
        if (cnt[s[r]]++ < 0) --missing;

        while (missing == 0) {
            if (r - l + 1 < min_len) {
                min_len = r - l + 1;
                start = l;
            }
            if (cnt[s[l]]-- == 0) ++missing;
            ++l;
        }
    }

    if (min_len == INF_MAX) return "";

    char* res = malloc(min_len + 1);
    memcpy(res, s + start, min_len);
    res[min_len] = '\0';

    return res;
}
