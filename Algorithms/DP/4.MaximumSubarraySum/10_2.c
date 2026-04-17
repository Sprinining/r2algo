#include <stdio.h>
#include <stdlib.h>

int* maxSumOfThreeSubarrays(int* nums, int numsSize, int k, int* returnSize) {
    // kSums[i] = i 位置开头的长为 k 的子数组累加和
    int* kSums = malloc(sizeof(*kSums) * numsSize);
    for (int l = 0, r = 0, s = 0; r < numsSize; ++r) {
        s += nums[r];
        if (r - l + 1 == k) {
            kSums[l] = s;
            s -= nums[l];
            ++l;
        }
    }

    // lmax_dp[i] = [0, i] 上长度为 k 的最大子数组的起始位置
    int* lmax_dp = malloc(sizeof(*lmax_dp) * numsSize);
    int lmax = 0x80000000;
    for (int i = k - 1; i < numsSize; ++i) {
        int begin = i - k + 1;
        // 保证字典序最小
        if (lmax < kSums[begin]) {
            lmax = kSums[begin];
            lmax_dp[i] = begin;
        } else {
            lmax_dp[i] = lmax_dp[i - 1];
        }
    }

    // rmax_dp[i] = [i, numsSize-1] 上长度为 k 的最大子数组的起始位置
    int* rmax_dp = malloc(sizeof(*rmax_dp) * numsSize);
    int rmax = 0x80000000;
    for (int i = numsSize - k; i >= 0; --i) {
        // 保证字典序最小
        if (rmax <= kSums[i]) {
            rmax = kSums[i];
            rmax_dp[i] = i;
        } else {
            rmax_dp[i] = rmax_dp[i + 1];
        }
    }

    *returnSize = 3;
    int* res = malloc(sizeof(*res) * 3);
    int maxSum = 0x80000000;
    // 遍历中间子数组的起始位置
    for (int i = k; i <= numsSize - 2 * k; ++i) {
        int total = kSums[lmax_dp[i - 1]] + kSums[i] + kSums[rmax_dp[i + k]];
        if (maxSum < total) {
            maxSum = total;
            res[0] = lmax_dp[i - 1];
            res[1] = i;
            res[2] = rmax_dp[i + k];
        }
    }

    return res;
}