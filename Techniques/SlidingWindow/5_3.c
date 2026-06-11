#include <stdbool.h>
#include <string.h>

#define MMIN(a, b) ((a) > (b) ? (b) : (a))

// 能否通过修改长度为 len 的滑动窗口，把字符串变成平衡字符串
bool ok(const int* counts, int len, int require) {
    for (int i = 0; i < 4; ++i) {
        // 窗口外的字符频率若超过 require，则无法消去多出来的字符
        if (counts[i] > require) {
            return false;
        }
        // 用长度 len 的窗口补齐每个字符缺失的个数 require - counts[i]
        len -= (require - counts[i]);
    }
    // 窗口刚好用完（或者如果有多余长度可以自由分配，由于总长度lenS是4的倍数，这里len最终会刚好等于0）
    return len == 0;
}

int balancedString(char* s) {
    int lenS = strlen(s);
    // 每种字符必须出现的次数
    int require = lenS / 4;

    // Q W E R 转换成 0 1 2 3，分配动态数组替代 vector<int> nums(lenS)
    // 为了省去 malloc
    // 的开销，直接在循环中动态转换即可，但为了百分百还原你的逻辑，我们直接使用原字符动态映射
    // 统计窗口外字符出现次数，初始化为 0
    int counts[4] = {0};
    for (int i = 0; i < lenS; ++i) {
        int idx =
            (s[i] == 'Q') ? 0 : ((s[i] == 'W') ? 1 : ((s[i] == 'E') ? 2 : 3));
        counts[idx]++;
    }

    // 最多调整整个数组
    int res = lenS;
    int r = 0;

    // 窗口 [l, r)
    for (int l = 0; l < lenS; ++l) {
        // 这里的 while 条件里，需要先确保 r < lenS 再调用 ok，防止右移越界
        while (r < lenS && !ok(counts, r - l, require)) {
            // 窗口右边移入，移入的字符在 counts 中的计数减一
            int idx_r = (s[r] == 'Q')
                            ? 0
                            : ((s[r] == 'W') ? 1 : ((s[r] == 'E') ? 2 : 3));
            counts[idx_r]--;
            r++;
        }

        // 再次检查当前窗口是否满足条件
        if (ok(counts, r - l, require)) {
            res = MMIN(res, r - l);
        }

        // 窗口左边移出，移出的字符在 counts 中的计数加一
        int idx_l =
            (s[l] == 'Q') ? 0 : ((s[l] == 'W') ? 1 : ((s[l] == 'E') ? 2 : 3));
        counts[idx_l]++;
    }

    return res;
}
