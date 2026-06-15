#include <stdlib.h>

#define MMAX(a, b) ((a) > (b) ? (a) : (b))

int longestSubarray(int* nums, int numsSize, int limit) {
    // 递减队列
    int* deque1 = malloc(sizeof(int) * numsSize);
    int f1 = 0, r1 = 0;
    // 递增队列
    int* deque2 = malloc(sizeof(int) * numsSize);
    int f2 = 0, r2 = 0;

    int res = 0;
    for (int l = 0, r = 0; r < numsSize; ++r) {
        while (f1 < r1 && nums[deque1[r1 - 1]] <= nums[r]) --r1;
        deque1[r1++] = r;
        while (f2 < r2 && nums[deque2[r2 - 1]] >= nums[r]) --r2;
        deque2[r2++] = r;

        while (nums[deque1[f1]] - nums[deque2[f2]] > limit) {
            ++l;
            if (deque1[f1] < l) ++f1;
            if (deque2[f2] < l) ++f2;
        }

        res = MMAX(res, r - l + 1);
    }

    return res;
}
