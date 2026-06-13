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

// 同样是双闭区间，但利用 while 条件作为安全伞
// 在迈出破坏性的下一步之前，提前在循环内部安全的结算答案
// 推荐：标准的“右指针单向右扩，左指针在内部 while 追赶”的黄金模板
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

        while (balance(r - l + 1)) {
            // 提前结算：趁着现在还合法，赶紧把当前的长度记录下来
            res = MMIN(res, r - l + 1);
            // 结算完后，再放心大胆地执行左缩
            ++cnt[s[l]];
            ++l;
        }
        // 无需回退：当 balance 失败退出 while，不合法的 l 没有机会污染 res
        // 完美的答案在上一次循环中已经被提前安全记录了
    }

    return res;
}
