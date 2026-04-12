#include <stdlib.h>

#define MMAX(a, b) ((a) > (b) ? (a) : (b))

// 必须经过 mid 位置的最大子数组和
int maxCrossSum(int* nums, int left, int right, int mid) {
    // 从 mid 往左延伸出的最大子数组和
    int maxLeft = nums[mid];
    // 从 mid 往右延伸出的最大子数组和
    int maxRight = nums[mid];

    for (int i = mid - 1, pre = nums[mid]; i >= left; --i) {
        pre += nums[i];
        maxLeft = MMAX(maxLeft, pre);
    }

    for (int i = mid + 1, pre = nums[mid]; i <= right; ++i) {
        pre += nums[i];
        maxRight = MMAX(maxRight, pre);
    }

    // 去掉重复计算的一次 nums[mid]
    return maxLeft - nums[mid] + maxRight;
}

// 返回区间 [left, right] 的最大子数组和
int maxSubArraySum(int* nums, int left, int right) {
    if (left > right) return 0x80000000;
    if (left == right) return nums[left];
    int mid = left + ((right - left) >> 1);
    // 在左区域
    int p1 = maxSubArraySum(nums, left, mid - 1);
    // 在右区域
    int p2 = maxSubArraySum(nums, mid + 1, right);
    // 经过 nums[mid]
    int p3 = maxCrossSum(nums, left, right, mid);
    return MMAX(p1, MMAX(p2, p3));
}

int maxSubArray(int* nums, int numsSize) { return maxSubArraySum(nums, 0, numsSize - 1); }