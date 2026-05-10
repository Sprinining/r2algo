#include <string.h>

#define MOD 1000000007
// 集合中值的范围 1～30
#define MAXV 30
// 每种 stat 要十位记录
#define STAT_LEN 10
// stat 最大值
#define STAT_MAX 0b1111111111

typedef long long ll;

// prime[i] = i对应的 stat
// 1.如果 i 拥有某个质因子超过 1 个，则认为这个数字无效，质因子状态 = 0b0000000000
//   比如 12，拥有 2 这种质数因子有 2 个
// 2.如果 i 拥有任何一种质因子个数都不超过 1，则认为有效，用位信息表示质因子状态
//   比如 14，拥有质因子 2 和 7 都不超过 1 个
// 质数: 29 23 19 17 13 11 7 5 3 2
// 位置:  9  8  7  6  5  4 3 2 1 0
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

// nums[i] 范围 [1, 30]
int cnts[MAXV + 1];

// [1, idx] 的所有子集中，子集所有元素相乘，乘积的质因子状态是 stat 的子集个数
int dfs(int idx, int stat) {
    if (idx == 1) {
        // 只有元素 1 可选
        // stat != 0 说明最终拼不出来质因子状态为 stat 的集合
        if (stat != 0) return 0;
        // stat == 0 说明已经拼出来了
        // 但是还有好多个 1 可选，乘到最终的乘积上并不会改变 stat
        // 1 有 2^cnts[i] 种排列组合
        int res = 1;
        for (int i = 0; i < cnts[1]; ++i) res = (res << 1) % MOD;
        return res;
    } else {
        // 还有好多元素可选
        // p1: 不要当前的这个元素
        int res = dfs(idx - 1, stat);
        // p2：要当前的元素
        int cnt = cnts[idx];        // idx 的出现次数
        int cur_stat = prime[idx];  // idx 的质因子状态
        // 首先集合中必须有这个数，而且是有效数字
        // 其次 stat 中为 0 的位置，cur_stat 对应位置确是 1，那么也不能选
        if (cnt != 0 && cur_stat != 0 && (cur_stat & stat) == cur_stat) {
            res = (res + (ll)cnt * dfs(idx - 1, cur_stat ^ stat)) % MOD;
        }
        return res;
    }
}

int numberOfGoodSubsets(int* nums, int numsSize) {
    memset(cnts, 0, sizeof(cnts));
    // 统计每种数字出现的次数
    for (int i = 0; i < numsSize; ++i) ++cnts[nums[i]];

    int res = 0;
    // 每次都从所有的元素里进行挑选，看看能不能凑出乘积的质因子状态为 stat 的子集
    // 尝试每一种 stat，累计结果
    for (int stat = 1; stat <= STAT_MAX; ++stat) {
        res = ((ll)res + dfs(MAXV, stat)) % MOD;
    }
    return res;
}
