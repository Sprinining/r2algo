#include <stdlib.h>

int* maxSlidingWindow(int* nums, int numsSize, int k, int* returnSize) {
    *returnSize = numsSize - k + 1;
    int* res = malloc(sizeof(int) * (*returnSize));
    int idx = 0;

    // 单调递减双端队列，队列中存储的是元素的下标
    int* deque = malloc(sizeof(int) * numsSize);
    int front = 0, rear = 0;

    for (int r = 0; r < numsSize; ++r) {
        // 保持队列单调递减：如果新元素大于等于队尾元素，就把队尾踢出
        while (front < rear && nums[deque[rear - 1]] <= nums[r]) --rear;
        // 将当前元素的下标压入队尾
        deque[rear++] = r;

        // 检查队头元素是否滑出了当前窗口的左边界
        if (deque[front] <= r - k) ++front;

        // 当右指针走到 k - 1 及之后
        // 说明窗口已成型，开始记录每个窗口的队头最大值
        if (r >= k - 1) res[idx++] = nums[deque[front]];
    }

    return res;
}
