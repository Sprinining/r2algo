#include <stdlib.h>

#define MMAX(a, b) ((a) > (b) ? (a) : (b))

int best(int* nums, int left, int right) {
    if (left > right) return 0;
    if (left == right) return nums[left];
    // dp[i-2]
    int l = nums[left];
    // dp[i-1]
    int m = MMAX(nums[left], nums[left + 1]);
    // dp[i]
    int r = m;
    for (int i = left + 2; i <= right; ++i) {
        r = MMAX(l + nums[i], m);
        l = m;
        m = r;
    }
    return r;
}

int rob(int* nums, int numsSize) {
    if (numsSize == 1) return nums[0];
    // nums[0] 选或者不选两种情况
    return MMAX(nums[0] + best(nums, 2, numsSize - 2), best(nums, 1, numsSize - 1));
}