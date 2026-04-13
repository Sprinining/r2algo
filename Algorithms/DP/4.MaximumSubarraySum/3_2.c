#include <stdlib.h>
#define MMAX(a, b) ((a) > (b) ? (a) : (b))
#define MMIN(a, b) ((a) > (b) ? (b) : (a))

int maxSubarraySumCircular(int* nums, int numsSize) {
    // 数组总和
    int sum = nums[0];
    // 子数组最大累加和（不跨环）
    int maxSum = nums[0];
    int maxPre = nums[0];
    // 子数组最小累加和（不跨环）
    int minSum = nums[0];
    int minPre = nums[0];
    for (int i = 1; i < numsSize; ++i) {
        sum += nums[i];

        maxPre = ((maxPre > 0) ? maxPre : 0) + nums[i];
        maxSum = MMAX(maxSum, maxPre);

        minPre = ((minPre < 0) ? minPre : 0) + nums[i];
        minSum = MMIN(minSum, minPre);
    }

    // 两种情况：
    // 1. 不跨环：就是 maxSum
    // 2. 跨环：等价于总和 - 中间最小子数组 = sum - minSum

    // 特殊情况：所有元素都是负数
    // 此时 sum == minSum（整个数组就是最小子数组）
    // 不能用 sum - minSum = 0，因为不能选空数组，必须返回 maxSum（即最大那个负数）
    return sum == minSum ? maxSum : MMAX(maxSum, sum - minSum);
}