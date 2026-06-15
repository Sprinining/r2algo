#include <string.h>

#define MMAX(a, b) ((a) > (b) ? (a) : (b))

int dfs(char* s, int start, int end, int k) {
    if (end - start + 1 < k) return 0;

    // 统计当前区间内每个字符出现的频次
    int cnt[128] = {0};
    for (int i = start; i <= end; ++i) ++cnt[s[i]];

    // 寻找第一个“不合法”的字符作为切分点
    for (int i = start; i <= end; ++i) {
        if (cnt[s[i]] > 0 && cnt[s[i]] < k) {
            // 递归计算切分点左边和右边的最大长度
            int left = dfs(s, start, i - 1, k);
            int right = dfs(s, i + 1, end, k);
            return MMAX(left, right);
        }
    }

    // 如果所有出现过的字符频次都 >= k，说明当前整段字符串都合法
    return end - start + 1;
}

// 扫描当前区间并找出所有频次不足 k 次的不达标字符
// 因为任何包含它们的子串都注定不合法
// 以这些不达标字符为分界点将字符串拦腰切断，然后递归地去各个被切开的子区间内寻找解
// 最终取各区间的最大值
int longestSubstring(char* s, int k) { return dfs(s, 0, strlen(s) - 1, k); }
