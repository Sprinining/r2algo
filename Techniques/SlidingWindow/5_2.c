#include <string.h>

#define MMIN(a, b) ((a) > (b) ? (b) : (a))

int balancedString(char* s) {
    int len = strlen(s);
    int limit = len / 4;

    int cnt[128] = {0};
    for (int i = 0; i < len; ++i) ++cnt[s[i]];

    if (cnt['Q'] <= limit && cnt['W'] <= limit && cnt['E'] <= limit &&
        cnt['R'] <= limit)
        return 0;

    int res = len;
    int l = 0;

    // r 右扩
    for (int r = 0; r < len; ++r) {
        // 进入窗口的字符，相当于在窗口外消失了，所以频次减 1
        --cnt[s[r]];

        // 当窗口外的所有字符都满足 <= limit 时，说明当前窗口是一个可行解
        while (cnt['Q'] <= limit && cnt['W'] <= limit && cnt['E'] <= limit &&
               cnt['R'] <= limit) {
            // 更新全局最小值
            res = MMIN(res, r - l + 1);

            // l 左缩
            ++cnt[s[l]];
            ++l;
        }
    }

    return res;
}
