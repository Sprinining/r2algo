#include <stdlib.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))

// 空间优化
int maxSubArray(int* nums, int numsSize) {
    int res = nums[0];
    for (int i = 1, pre = nums[0]; i < numsSize; ++i) {
        pre = ((pre > 0) ? pre : 0) + nums[i];
        res = MAX(res, pre);
    }

    return res;
}