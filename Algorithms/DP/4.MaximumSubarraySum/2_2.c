#include <stdlib.h>

#define MMAX(a, b) ((a) > (b) ? (a) : (b))

// 空间压缩
int rob(int* nums, int numsSize) {
    if (numsSize == 1) return nums[0];
    int left = nums[0];
    int mid = MMAX(nums[0], nums[1]);
    int right = mid;
    for (int i = 2; i < numsSize; ++i) {
        // 当前位置偷不偷两种情况
        right = MMAX(left + nums[i], mid);
        left = mid;
        mid = right;
    }

    return right;
}