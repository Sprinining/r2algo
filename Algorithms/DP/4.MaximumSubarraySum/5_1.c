#include <stdlib.h>

#define MMAX(a, b) ((a) > (b) ? (a) : (b))
#define MMIN(a, b) ((a) > (b) ? (b) : (a))

// 以 ability 偷窃能力最多能偷到的房间数
int maxLoot(int* nums, int numsSize, int ability) {
    if (numsSize == 1) return nums[0] <= ability ? 1 : 0;
    if (numsSize == 2) return (nums[0] <= ability || nums[1] <= ability) ? 1 : 0;
    // 空间压缩
    int l = nums[0] <= ability ? 1 : 0;
    int m = (nums[0] <= ability || nums[1] <= ability) ? 1 : 0;
    int r = m;
    for (int i = 2; i < numsSize; ++i) {
        // 当前位置偷或者不偷
        r = MMAX(l + (nums[i] <= ability ? 1 : 0), m);
        l = m;
        m = r;
    }
    return r;
}

int minCapability(int* nums, int numsSize, int k) {
    // 记录房屋金额的上下限，也就是偷窃能力的范围
    int minAbility = nums[0];
    int maxAbility = nums[0];
    for (int i = 0; i < numsSize; ++i) {
        minAbility = MMIN(minAbility, nums[i]);
        maxAbility = MMAX(maxAbility, nums[i]);
    }

    // 找到第一个能至少偷到 k 间房子的偷窃能力
    int left = minAbility;
    int right = maxAbility;
    int mid;
    while (left <= right) {
        mid = left + ((right - left) >> 1);
        if (maxLoot(nums, numsSize, mid) >= k) {
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }

    return left;
}