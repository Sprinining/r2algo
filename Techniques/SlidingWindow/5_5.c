#include <stdbool.h>
#include <string.h>

#define MMIN(a, b) ((a) > (b) ? (b) : (a))

// 窗口外的字符出现次数
int cnt[4];
// 每种字符应该出现的次数
int limit;

// 除去长度为 len 的窗口，之外的字符个数是否小于等于 limit
// 这样才能平衡
bool balance(int len) {
    for (int i = 0; i < 4; ++i) {
        if (cnt[i] > limit) return false;
        // 从窗口中挑选字符弥补
        len -= (limit - cnt[i]);
    }
    // 是否完全弥补
    return len == 0;
}

// 采用先斩后奏策略
// while 循环会一直缩减 l 直到窗口不平衡才弹出来，然后再手动回退状态
// 拉跨
int balancedString(char* s) {
    int n = strlen(s);
    limit = n >> 2;
    memset(cnt, 0, sizeof(cnt));

    // 转换为 0～3
    for (int i = 0; i < n; ++i) {
        char ch = s[i];
        int idx = (ch == 'Q') ? 0 : (ch == 'W' ? 1 : (ch == 'E' ? 2 : 3));
        s[i] = idx;
        ++cnt[idx];
    }

    if (balance(0)) return 0;

    int res = n;
    // [l, r]
    for (int l = 0, r = 0; r < n; ++r) {
        --cnt[s[r]];
        if (!balance(r - l + 1)) continue;

        // 只要平衡就一直缩，缩到不平衡了才会跌出 while 循环
        while (balance(r - l + 1)) {
            ++cnt[s[l]];
            ++l;
        }

        // 撤销与回滚：既然上面跌出了循环，说明此时的 l 已经缩过头导致不合法了
        --l;
        --cnt[s[l]];
        res = MMIN(res, r - l + 1);
    }

    return res;
}
