#include <string.h>

#define MMAX(a, b) ((a) > (b) ? (a) : (b))

// 记录每个字符上一次出现的位置
int last[128];

int lengthOfLongestSubstring(char* s) {
    int n = strlen(s);
    memset(last, -1, sizeof(last));

    int res = 0;
    for (int l = 0, r = 0; r < n; ++r) {
        // 表示如果当前字符曾经出现过，左指针应该直接跳到它上一次出现位置的下一个位置
        l = MMAX(l, last[s[r]] + 1);
        res = MMAX(res, r - l + 1);
        last[s[r]] = r;
    }

    return res;
}
