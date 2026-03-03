#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 暴力递归
int func(int* nums, int n, int target, int idx, int sum) {
    if (idx == n) return sum == target ? 1 : 0;
    return func(nums, n, target, idx + 1, sum + nums[idx]) +
           func(nums, n, target, idx + 1, sum - nums[idx]);
}

int findTargetSumWays(int* nums, int numsSize, int target) {
    return func(nums, numsSize, target, 0, 0);
}