#include <stdbool.h>

int nums[10];
int nums_cnt;
int limit;
int table[10];

// 返回位数刚好为 len 的情况总数 
int dfs(int len, int offset) {
    // 拼出来的刚好是 limit
    if (len == 0) return 1;
    int res = 0;
    // limit 当前位的数字 
    int cur = (limit / offset) % 10;
    for (int i = 0; i < nums_cnt; ++i) {
        if (nums[i] < cur) {
            res += table[len - 1];
        } else if (nums[i] == cur) {
            res += dfs(len - 1, offset / 10);
        } else {
            break;
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

    int res = 0;
    // table[i] = i 个位置都随便选的情况总数
    table[0] = 1;
    for (int i = 1; i < len; ++i) {
        table[i] = table[i - 1] * nums_cnt;
        // 先加上位数小于 len 的所有情况，之后只用计算位数为 len 的情况
        res += table[i];
    }
    return res + dfs(len, offset);
}
