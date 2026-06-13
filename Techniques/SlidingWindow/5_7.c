#include <string.h>

#define MMIN(a, b) ((a) > (b) ? (b) : (a))

int balancedString(char* s) {
    int n = strlen(s);
    int limit = n >> 2;

    int counts[4] = {0};
    for (int i = 0; i < n; ++i) {
        char ch = s[i];
        int idx = (ch == 'Q') ? 0 : (ch == 'W' ? 1 : (ch == 'E' ? 2 : 3));
        s[i] = idx;
        ++counts[idx];
    }

    // 计算债务
    int debt = 0;
    for (int i = 0; i < 4; ++i) {
        if (counts[i] < limit) {
            counts[i] = 0;
        } else {
            // 多出来的个数记为负数
            counts[i] = limit - counts[i];
            debt -= counts[i];
        }
    }

    if (debt == 0) return 0;

    int res = n;
    // [l, r] 左闭右闭，以 r 为外层循环
    for (int l = 0, r = 0; r < n; ++r) {
        // 右扩：如果当前字符是“债主”，进窗意味着还了一块债
        if (counts[s[r]] < 0) --debt;
        ++counts[s[r]];
        if (debt != 0) continue;

        // 债务还清了，左边开始拼命缩
        // 如果 counts[s[l]] > 0
        // 说明这个字符在窗内属于多余的，可以安全吐出
        while (counts[s[l]] > 0) {
            --counts[s[l]];
            ++l;
        }
        res = MMIN(res, r - l + 1);
    }

    return res;
}
