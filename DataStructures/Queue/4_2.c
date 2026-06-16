#include <stdlib.h>

#define MMIN(a, b) ((a) > (b) ? (b) : (a))
#define INF_MAX 0x3f3f3f3f
#define ll long long

int shortestSubarray(int* nums, int numsSize, int k) {
    // pre_sum[i] 表示前 i 个元素的和，用 ll 防大数溢出
    ll* pre_sum = malloc(sizeof(ll) * (numsSize + 1));
    pre_sum[0] = 0;
    for (int i = 0; i < numsSize; ++i) {
        pre_sum[i + 1] = pre_sum[i] + nums[i];
    }

    // deque 存放 pre_sum下标，保持对应值严格单调递增
    int* deque = malloc(sizeof(int) * (numsSize + 1));
    int front = 0, rear = 0;

    int res = INF_MAX;
    for (int l = 0, r = 0; r <= numsSize; ++r) {
        // 维护队尾单调性
        while (front < rear && pre_sum[deque[rear - 1]] >= pre_sum[r]) --rear;
        deque[rear++] = r;

        // 缩小窗口
        while (pre_sum[r] - pre_sum[deque[front]] >= k) {
            res = MMIN(res, r - deque[front]);

            // l 在此处作为步进计数器与 front 协同工作：
            // 1. l 自增但未超过队头时，front 不变，继续循环
            // 2. l 超过队头时，if 触发，++front 执行，切换新队头
            ++l;
            if (deque[front] < l) ++front;
        }
    }

    return res == INF_MAX ? -1 : res;
}
