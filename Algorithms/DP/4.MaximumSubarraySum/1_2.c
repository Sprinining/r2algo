#include <stdlib.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))

// 空间优化
int maxSubArray(int* nums, int numsSize) {
    int res = nums[0];
    int pre = nums[0];
    for (int i = 1; i < numsSize; ++i) {
        // pre = ((pre > 0) ? pre : 0) + nums[i];
        pre = MAX(nums[i], pre + nums[i]);
        res = MAX(res, pre);
    }

    return res;
}