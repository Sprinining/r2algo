#include <string.h>

#define MMAX(a, b) ((a) > (b) ? (a) : (b))

// 窗口内每个字符出现的次数
int cnt[128];
// 窗口内不同字符的种类数
int kind;
// 当前窗口内出现次数大于等于 k的字符种类数
int satisfy;
int n;

// 限定当前窗口内最多且必须包含的不同字符种类数
int func(char* s, int k, int limit) {
    memset(cnt, 0, sizeof(cnt));
    kind = 0;
    satisfy = 0;

    int res = 0;
    for (int l = 0, r = 0; r < n; ++r) {
        ++cnt[s[r]];
        if (cnt[s[r]] == 1) ++kind;
        if (cnt[s[r]] == k) ++satisfy;

        // 人为制造的单调性：一旦窗口内实际字符种类超出了当前允许的 limit 限制
        // 左边界 l 必须无脑向右移动，直到窗口内的字符种类降回 limit 以内
        while (kind > limit) {
            --cnt[s[l]];
            if (cnt[s[l]] == 0) --kind;
            if (cnt[s[l]] == k - 1) --satisfy;
            ++l;
        }

        if (kind == satisfy && satisfy == limit) res = MMAX(res, r - l + 1);
    }

    return res;
}
// 通过在外层循环强行固定一个“数量上限”或“目标特征”（比如限定窗口内只能有几种字符）
// 将原本进退两难的模糊状态转化为明确的边界
// 在这个硬性限制下，右指针右移必然导致状态向着超标靠拢，左指针右移必然导致状态从超标回落
// 从而人为构造出双指针所需的单调性
int longestSubstring(char* s, int k) {
    n = strlen(s);
    int res = 0;

    for (int i = 1; i <= 26; ++i) res = MMAX(res, func(s, k, i));

    return res;
}
