#include <stdio.h>
#include <stdlib.h>

// 空间优化
int maxSubArray(int* nums, int numsSize) {
    int pre = nums[0];
    int res = nums[0];

    // 最大子数组的两端
    int begin = 0, end = 0;
    int start = 0;
    for (int i = 1; i < numsSize; ++i) {
        if (pre > 0) {
            pre += nums[i];
        } else {
            pre = nums[i];
            start = i;
        }
        if (pre > res) {
            res = pre;
            begin = start;
            end = i;
        }
    }

    printf("%d %d", begin, end);
    return res;
}