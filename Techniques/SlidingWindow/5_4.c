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

// 同样是外层 l 控制，但强制使用双闭区间 [l, r]
// 为此必须在循环前手动处理 s[0]
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

    // 由于定义是 [0, 0] 双闭区间开始，刚进来时 s[0] 已经在窗内了
    // 必须手动在外部把 s[0] 的外部计数减掉
    if (balance(0)) return 0;

    int res = n;
    // [l, r]，左闭右闭
    // 以 l 为循环变量
    --cnt[s[0]];
    for (int l = 0, r = 0; l < n; ++l) {
        while (r < n - 1 && !balance(r - l + 1)) {
            ++r;
            --cnt[s[r]];
        }
        if (balance(r - l + 1)) res = MMIN(res, r - l + 1);
        ++cnt[s[l]];
    }

    return res;
}
