#include <stdlib.h>

#define MMAX(a, b) ((a) > (b) ? (a) : (b))
#define MMIN(a, b) ((a) > (b) ? (b) : (a))

// 以 ability 偷窃能力最多能偷到的房间数
int maxLoot(int* nums, int numsSize, int ability) {
    int cur = 0;
    int res = 0;
    while (cur < numsSize) {
        // 每个能偷的地方收益都是 1，所以尽早偷，让后面的范围更大
        if (nums[cur] <= ability) {
            res++;
            cur += 2;
        } else {
            cur++;
        }
    }

    return res;
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