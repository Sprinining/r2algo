#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MMAX(a, b) ((a) > (b) ? (a) : (b))
#define MMIN(a, b) ((a) > (b) ? (b) : (a))

// 给定一个数组 nums，求必须删除一个数字后的新数组中，长度为 k 的子数组最大累加和

#include <limits.h>
#include <stdio.h>

#define MMAX(a, b) ((a) > (b) ? (a) : (b))

// 在跳过 skip 位置的情况下求长度为 k 的最大子数组和
int lenKMaxSumSkip(int* nums, int numsSize, int k, int skip) {
    int res = 0x80000000;
    for (int i = 0; i < numsSize; ++i) {
        int cur = 0;
        int cnt = 0;
        for (int j = i; j < numsSize && cnt < k; ++j) {
            // 跳过删除点
            if (j == skip) continue;
            cur += nums[j];
            cnt++;
        }
        if (cnt == k) res = MMAX(res, cur);
    }

    return res;
}

// 暴力
int func1(int* nums, int numsSize, int k) {
    int res = 0x80000000;
    for (int skip = 0; skip < numsSize; ++skip) {
        res = MMAX(res, lenKMaxSumSkip(nums, numsSize, k, skip));
    }

    return res;
}

// 转化为每个长度 k+1 的窗口：sum - min
int func2(int* nums, int numsSize, int k) {
    int res = 0x80000000;
    // 单调队列保存长度 k+1 的窗口的最小值的下标，队头是窗口最小值
    int* deque = malloc(sizeof(*deque) * numsSize);
    int head = 0, tail = 0;
    for (int l = 0, r = 0, s = 0; r < numsSize; ++r) {
        // 窗口累加和
        s += nums[r];
        // 如果当前值更小，那么队尾所有比它大的元素都没用了（永远不可能成为最小值）
        while (head < tail && nums[deque[tail - 1]] >= nums[r]) --tail;
        deque[tail++] = r;
        // 窗口长度 k+1
        if (r - l == k) {
            // 不在窗口中就从队头弹出
            while (head < tail && deque[head] < l) ++head;
            res = MMAX(res, s - nums[deque[head]]);
            s -= nums[l];
            ++l;
        }
    }
    return res;
}

bool judge() {
    int numsSize = 100;
    int* nums = malloc(sizeof(*nums) * numsSize);
    for (int i = 0; i < numsSize; ++i) nums[i] = rand() % 21 - 10;
    int s1 = func1(nums, numsSize, 7);
    int s2 = func2(nums, numsSize, 7);
    if (s1 != s2) {
        printf("error: %d %d\n", s1, s2);
        return false;
    }
    return true;
}

int main() {
    srand(time(NULL));
    int trials = 10000;
    for (int i = 0; i < trials; ++i) {
        if (!judge()) exit(EXIT_FAILURE);
    }
    printf("all success\n");
}