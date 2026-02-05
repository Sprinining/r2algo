#include <stdlib.h>
#include <string.h>
int mmax(int a, int b) { return a > b ? a : b; }

int findSubstringInWraproundString(char* s) {
    int len = strlen(s);
    if (len == 1) return 1;
    // dp[i] 若表示 s[0...i] 在 base 中出现的不同非空子串个数，不好处理
    // dp[i] 若表示必须以当前字符 s[i] 结尾的在 base
    // 中出现的不同非空子串个数，最后汇总会有重复的，因为 s 中会有重复字符
    // dp[i] 表示必须以字符 i + 'a' 结尾的在 base
    // 中出现的不同非空子串个数，也就是把必须以字符 ch 结尾的合法长度映射到
    // dp[ch-'a']，最后汇总不会有重复，因为
    // 26 个字符每个只统计了一个最大的合法长度
    int* dp = (int*)calloc(26, sizeof(int));
    dp[s[0] - 'a'] = 1;
    int count = 1;
    for (int i = 1; i < len; i++) {
        char cur = s[i];
        char pre = s[i - 1];
        if ((cur - pre + 26) % 26 == 1) {
            // 接上
            count++;
        } else {
            // 没接上就重置
            count = 1;
        }
        // count 表示这个合法子串的长度，刚好也能表示表示必须以字符 cur
        // 结尾的在 base 中出现的不同非空子串个数
        dp[cur - 'a'] = mmax(dp[cur - 'a'], count);
    }

    int sum = 0;
    for (int i = 0; i < 26; i++) sum += dp[i];
    return sum;
}