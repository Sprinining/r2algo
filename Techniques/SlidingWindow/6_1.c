#include <string.h>

#define MAXN 20005

int cnt[MAXN];
int kind;

// 整数个数小于等于 k 的好子数组个数
int func(int* nums, int n, int k) {
    kind = 0;
    memset(cnt, 0, sizeof(cnt));

    int res = 0;
    for (int l = 0, r = 0; r < n; ++r) {
        if (cnt[nums[r]] == 0) ++kind;
        ++cnt[nums[r]];

        while (kind > k) {
            --cnt[nums[l]];
            if (cnt[nums[l]] == 0) --kind;
            ++l;
        }
        // 以 r 结尾的有效子数组
        res += r - l + 1;
    }

    return res;
}

// 整数个数等于 k 的好子数组个数
int subarraysWithKDistinct(int* nums, int numsSize, int k) {
    // 单调性转化
    return func(nums, numsSize, k) - func(nums, numsSize, k - 1);
}
