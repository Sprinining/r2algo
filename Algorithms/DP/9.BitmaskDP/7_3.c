#include <string.h>

#define MOD 1000000007
#define MAXV 30
#define STAT_LEN 10
#define STAT_MAX 0b1111111111

typedef long long ll;

// prime[i] = i对应的质因子状态
int prime[31] = {
    0b0000000000,  // 0
    0b0000000000,  // 1
    0b0000000001,  // 2
    0b0000000010,  // 3
    0b0000000000,  // 4
    0b0000000100,  // 5
    0b0000000011,  // 6
    0b0000001000,  // 7
    0b0000000000,  // 8
    0b0000000000,  // 9
    0b0000000101,  // 10
    0b0000010000,  // 11
    0b0000000000,  // 12
    0b0000100000,  // 13
    0b0000001001,  // 14
    0b0000000110,  // 15
    0b0000000000,  // 16
    0b0001000000,  // 17
    0b0000000000,  // 18
    0b0010000000,  // 19
    0b0000000000,  // 20
    0b0000001010,  // 21
    0b0000010001,  // 22
    0b0100000000,  // 23
    0b0000000000,  // 24
    0b0000000000,  // 25
    0b0000100001,  // 26
    0b0000000000,  // 27
    0b0000000000,  // 28
    0b1000000000,  // 29
    0b0000000111   // 30
};

int cnts[MAXV + 1];

// dp[stat]
// 当前能够拼出 stat 的方案数
int dp[1 << STAT_LEN];

int numberOfGoodSubsets(int* nums, int numsSize) {
    memset(cnts, 0, sizeof(cnts));
    // 统计每个数字出现次数
    for (int i = 0; i < numsSize; ++i) ++cnts[nums[i]];

    memset(dp, 0, sizeof(dp));

    // 先处理数字 1
    // 1 不影响任何质因子状态
    int ways = 1;
    for (int i = 0; i < cnts[1]; ++i) ways = (ways << 1) % MOD;
    dp[0] = ways;

    // 枚举数字 2~30
    for (int idx = 2; idx <= MAXV; ++idx) {
        int cnt = cnts[idx];
        int cur_stat = prime[idx];
        // 没出现 or 非法数字
        if (cnt == 0 || cur_stat == 0) continue;
        // 倒序枚举
        // 防止同一个数字重复使用
        for (int stat = STAT_MAX; stat >= cur_stat; --stat) {
            // stat 必须包含 cur_stat
            if ((cur_stat & stat) == cur_stat) {
                dp[stat] = (dp[stat] + (ll)cnt * dp[cur_stat ^ stat]) % MOD;
            }
        }
    }

    // 去掉空集
    int res = 0;
    for (int stat = 1; stat <= STAT_MAX; ++stat) {
        res = ((ll)res + dp[stat]) % MOD;
    }

    return res;
}
