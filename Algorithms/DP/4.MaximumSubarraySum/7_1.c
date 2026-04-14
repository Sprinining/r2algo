#include <stdlib.h>
#include <string.h>

#define MMAX(a, b) ((a) > (b) ? (a) : (b))
#define MMIN(a, b) ((a) > (b) ? (b) : (a))

int maxProduct(int* nums, int numsSize) {
    int minPre = nums[0];
    int maxPre = nums[0];
    int res = nums[0];

    for (int i = 1; i < numsSize; ++i) {
        // 当前最小乘积三种情况：
        // 1. 只选自己
        // 2. 接在之前最小后面（负 * 负 = 正）
        // 3. 接在之前最大后面
        int curMin = MMIN(nums[i], MMIN(nums[i] * minPre, nums[i] * maxPre));
        int curMax = MMAX(nums[i], MMAX(nums[i] * minPre, nums[i] * maxPre));
        // 防止计算 curMax 的时候用的是刚被更新的 minPre
        minPre = curMin;
        maxPre = curMax;
        res = MMAX(res, maxPre);
    }
    return res;
}