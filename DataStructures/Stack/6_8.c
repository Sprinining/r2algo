#include <stdlib.h>

#define MMAX(a, b) ((a) > (b) ? (a) : (b))

int maxWidthRamp(int* nums, int numsSize) {
    int n = numsSize;
    if (n < 2) return 0;

    // 右侧最大值
    int* right_max = malloc(sizeof(int) * n);
    right_max[n - 1] = nums[n - 1];
    for (int i = n - 2; i >= 0; --i)
        right_max[i] = MMAX(nums[i], right_max[i + 1]);

    int l = 0, r = 0;
    int res = 0;

    while (r < n) {
        // 如果当前左指针的值，小于等于右指针及其右边的最大值
        // 说明以 l 为起点，最远能一直扩展到 r（甚至更远）
        if (nums[l] <= right_max[r]) {
            res = MMAX(res, r - l);
            ++r;
        } else {
            // 尝试换一个更小的起点
            ++l;
        }
    }

    return res;
}
