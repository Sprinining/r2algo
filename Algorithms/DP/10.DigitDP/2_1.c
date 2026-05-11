#include <stdbool.h>

int nums[10];
int nums_cnt;
int limit;

// 剩下 len 位没有确定
// free 为 true 表示之前的位已经确定比 limit 小，后续的数字可以随便选
// free 为 false 表示之前的位和 limit 一样，剩下的数字不能大于 limit 当前位的数字
// started 为 false 表示之前的位都没选过数字
int dfs(int len, int offset, bool free, bool started) {
    if (len == 0) return started ? 1 : 0;
    int res = 0;
    // p1：当前位置不选数字
    if (!started) res += dfs(len - 1, offset / 10, true, false);
    if (free) {
        // p2：当前位置随便选数字
        res += nums_cnt * dfs(len - 1, offset / 10, true, true);
    } else {
        // p3：当前位不能超过 limit 当前位的数字 cur
        int cur = (limit / offset) % 10;
        // nums[i] 非递减
        for (int i = 0; i < nums_cnt; ++i) {
            if (nums[i] < cur) {
                res += dfs(len - 1, offset / 10, true, true);
            } else if (nums[i] == cur) {
                res += dfs(len - 1, offset / 10, false, true);
            } else {
                break;
            }
        }
    }
    return res;
}

int atMostNGivenDigitSet(char** digits, int digitsSize, int n) {
    limit = n;
    nums_cnt = digitsSize;
    // n = 34242
    // len = 5
    // offset = 10000
    // limit 的位数
    int len = 1;
    // 帮助提取 limit 最高位的数：(limit/offset)%10
    int offset = 1;
    int temp = limit / 10;
    while (temp != 0) {
        ++len;
        offset *= 10;
        temp /= 10;
    }

    for (int i = 0; i < nums_cnt; ++i) nums[i] = digits[i][0] - '0';
    return dfs(len, offset, false, false);
}
