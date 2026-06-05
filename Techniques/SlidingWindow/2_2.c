#include <string.h>

#define MMAX(a, b) ((a) > (b) ? (a) : (b))

int cnt[128];

int lengthOfLongestSubstring(char* s) {
    memset(cnt, 0, sizeof(cnt));
    int n = strlen(s);
    int res = 0;

    // 右指针 r 负责向右扩展窗口
    for (int l = 0, r = 0; r < n; ++r) {
        // 将右指针当前指向的字符加入窗口，并记录其出现次数
        ++cnt[s[r]];

        // 如果当前字符的计数大于 1，说明窗口内出现了重复字符（即 s[r] 重复了）
        // 左边界向右收缩
        while (cnt[s[r]] > 1) {
            --cnt[s[l]];
            ++l;
        }

        res = MMAX(res, r - l + 1);
    }

    return res;
}
