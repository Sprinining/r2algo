#include <stdlib.h>
#define MMAX(a, b) ((a) > (b) ? (a) : (b))

// 暴力解空间压缩
int maxSubarraySumCircular(int* nums, int numsSize) {
    int res = nums[0];
    // 枚举每个起点 k
    for (int k = 0; k < numsSize; ++k) {
        int pre = nums[k];
        res = MMAX(res, pre);
        for (int i = 1; i < numsSize; ++i) {
            if (pre > 0) {
                pre += nums[(k + i) % numsSize];
            } else {
                pre = nums[(k + i) % numsSize];
            }
            res = MMAX(res, pre);
        }
    }

    return res;
}