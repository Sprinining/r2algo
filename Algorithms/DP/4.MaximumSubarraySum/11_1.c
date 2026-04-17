#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MMAX(a, b) ((a) > (b) ? (a) : (b))

// 给定一个数组 nums，现在允许随意选择数组连续一段进行翻转，也就是子数组逆序的调整
// 返回必须随意翻转 1 次之后，子数组的最大累加和

void reverse(int* nums, int l, int r) {
    while (l < r) {
        int a = nums[l];
        nums[l] = nums[r];
        nums[r] = a;
        ++l;
        --r;
    }
}

int maxSubSum(int* nums, int numsSize) {
    int res = nums[0];
    int pre = nums[0];
    for (int i = 1; i < numsSize; ++i) {
        pre = MMAX(pre + nums[i], nums[i]);
        res = MMAX(res, pre);
    }
    return res;
}

// 暴力解
int func1(int* nums, int numsSize) {
    int res = 0x80000000;
    for (int i = 0; i < numsSize; ++i) {
        for (int j = i; j < numsSize; ++j) {
            reverse(nums, i, j);
            res = MMAX(res, maxSubSum(nums, numsSize));
            reverse(nums, i, j);
        }
    }
    return res;
}

int func2(int* nums, int numsSize) {
    // rmax_dp[i] = 必须从 i 起始的子数组最大累加和
    int* rmax_dp = malloc(sizeof(*rmax_dp) * numsSize);
    rmax_dp[numsSize - 1] = nums[numsSize - 1];
    for (int i = numsSize - 2; i >= 0; --i) {
        rmax_dp[i] = MMAX(rmax_dp[i + 1] + nums[i], nums[i]);
    }

    int res = 0x80000000;
    // [0, i] 上的子数组最大累加和
    int lmax = nums[0];
    int pre = nums[0];
    // 循环只计算了左边选一段 + 右边选一段的情况，也就是必须发生拼接
    for (int i = 1; i < numsSize; ++i) {
        res = MMAX(res, lmax + rmax_dp[i]);
        pre = MMAX(pre + nums[i], nums[i]);
        lmax = MMAX(lmax, pre);
    }

    // 但如果左侧整体是负贡献，那么最优解可能完全在左侧内部（不需要拼接）
    res = MMAX(res, lmax);
    return res;
}

bool judge() {
    int numsSize = 100;
    int* nums = malloc(sizeof(*nums) * numsSize);
    for (int i = 0; i < numsSize; ++i) nums[i] = rand() % 21 - 10;
    int s1 = func1(nums, numsSize);
    int s2 = func2(nums, numsSize);
    if (s1 != s2) {
        for (int i = 0; i < numsSize; ++i) printf("%d ", nums[i]);
        printf("\nerror: %d %d\n", s1, s2);
        return false;
    }
    return true;
}

int main() {
    srand(time(NULL));
    int trials = 1000;
    for (int i = 0; i < trials; ++i) {
        if (!judge()) exit(EXIT_FAILURE);
    }
    printf("all success\n");
}