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

    // deque 存放 pre_sum 下标，保持对应值严格单调递增
    int* deque = malloc(sizeof(int) * (numsSize + 1));
    int front = 0, rear = 0;

    int res = INF_MAX;
    // 此时只有右指针 r 在主导遍历，去掉了多余的 l
    for (int r = 0; r <= numsSize; ++r) {
        // 维护队尾单调性
        while (front < rear && pre_sum[deque[rear - 1]] >= pre_sum[r]) --rear;
        deque[rear++] = r;

        // 满足区间和 >= k 时，尝试缩减左边界找更短子数组
        while (pre_sum[r] - pre_sum[deque[front]] >= k) {
            res = MMIN(res, r - deque[front]);
            // 队头已完成了它的历史使命，直接无条件出队
            // 下一轮循环会自动检查新队头（即瞬移到下一个最优左边界）
            ++front;
        }
    }

    return res == INF_MAX ? -1 : res;
}
