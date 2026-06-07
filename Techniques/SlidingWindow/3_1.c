#include <limits.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

char* minWindow(char* s, char* t) {
    int m = strlen(s);
    int n = strlen(t);

    // 标记哪些字符是 t 中需要的
    bool related[128] = {false};
    // 记录 t 中每种字符所需的个数
    int cnt[128] = {0};
    // 记录 t 中有多少种不同的字符
    int kind = 0;
    for (int i = 0; i < n; ++i) {
        char ch = t[i];
        related[ch] = true;
        if (cnt[ch] == 0) ++kind;
        ++cnt[ch];
    }

    // 记录当前找到的最小覆盖子串长度
    int min_len = INT_MAX;
    // 记录最小覆盖子串的起始下标
    int start = 0;

    for (int l = 0, r = 0; r < m; ++r) {
        // 右指针扩充窗口
        char ch = s[r];
        if (!related[ch]) continue;
        --cnt[ch];
        if (cnt[ch] == 0) --kind;
        if (kind != 0) continue;

        // 左指针收缩窗口
        while (!related[s[l]] || cnt[s[l]] < 0) {
            // 如果吐出的是 t 中的多余字符，需要把它在哈希表里的频次补回来
            if (cnt[s[l]] < 0) ++cnt[s[l]];
            ++l;
        }

        if (r - l + 1 < min_len) {
            min_len = r - l + 1;
            start = l;
        }
    }

    if (min_len == INT_MAX) return "";

    char* res = malloc(sizeof(char) * (min_len + 1));
    for (int i = 0; i < min_len; ++i) res[i] = s[start + i];
    res[min_len] = '\0';

    return res;
}
