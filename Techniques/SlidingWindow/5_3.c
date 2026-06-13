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

    int res = n;
    // [l, r)
    // 以 l 为窗口起点，r 有扩，一旦窗口合法就停止
    for (int l = 0, r = 0; l < n; ++l) {
        while (r < n && !balance(r - l)) {
            --cnt[s[r]];
            ++r;
        }
        if (balance(r - l)) res = MMIN(res, r - l);
        ++cnt[s[l]];
    }

    return res;
}
