#include <stdlib.h>

int* maxSlidingWindow(int* nums, int numsSize, int k, int* returnSize) {
    *returnSize = numsSize - k + 1;
    int* res = malloc(sizeof(int) * (*returnSize));
    int idx = 0;

    // 单调递减队列
    int* deque = malloc(sizeof(int) * numsSize);
    int front = 0, rear = 0;

    for (int l = 0, r = 0; r < numsSize; ++r) {
        // 入队
        while (front < rear && nums[deque[rear - 1]] <= nums[r]) --rear;
        deque[rear++] = r;

        // 不在窗口内的出队
        if (deque[front] < l) ++front;

        if (r >= k - 1) {
            res[idx++] = nums[deque[front]];
            ++l;
        }
    }

    return res;
}
