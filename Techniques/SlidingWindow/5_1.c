#include <stdbool.h>
#include <string.h>

#define MMIN(a, b) ((a) > (b) ? (b) : (a))

// 通过差值计算出哪些字符多出来了
// 然后利用双指针去寻找一个刚好包含所有多余字符的最短窗口
int balancedString(char* s) {
    int len = strlen(s);
    int limit = len >> 2;

    // 多开点空间，映射方便
    // cnt 存的是每个字符多出现了几次
    int cnt[128] = {0};
    for (int i = 0; i < len; ++i) ++cnt[s[i]];

    // 标记哪些字符超标了
    bool related[128] = {false};
    // 统计一共有几种字符超标
    int kind = 0;
    for (int i = 0; i < 128; ++i) {
        cnt[i] -= limit;
        if (cnt[i] > 0) {
            related[i] = true;
            ++kind;
        }
    }
    if (kind == 0) return 0;
    // cnt[i] > 0 说明该字符多出现了几次
    // 应该把这些多出现的字符转换成 cnt[i] < 0 的那些字符
    // 只需要找包含这 kind 种字符及其自身出现的次数的最短子串

    int res = 0x3f3f3f3f;
    for (int l = 0, r = 0; r < len; ++r) {
        char ch = s[r];
        // 无关字符
        if (!related[ch]) continue;

        // 右扩时，如果某个超标字符被窗口覆盖，kind 减一
        if (--cnt[ch] == 0) --kind;
        // 只要还有超标字符没被窗口覆盖，继续右扩
        if (kind != 0) continue;

        // 左缩
        ch = s[l];
        while (!related[ch] || cnt[ch] < 0) {
            // 需要改变，但是改多了的
            if (cnt[ch] < 0) ++cnt[ch];
            ch = s[++l];
        }

        res = MMIN(res, r - l + 1);
    }

    return res;
}
