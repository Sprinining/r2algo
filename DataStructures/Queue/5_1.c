#include <stdlib.h>

#define MMAX(a, b) ((a) > (b) ? (a) : (b))
#define INF_MIN -0x3f3f3f3f

int findMaxValueOfEquation(int** points, int pointsSize, int* pointsColSize,
                           int k) {
    // 为何这么构建队列？
    // 1. 目标方程变形为：(Yr + Xr) + (Yi - Xi)，i 是历史点，r 是当前点
    // 2. 站在 r 视角，Yr + Xr 是死值。
    //    想让总和最大，等价于找一个历史点 i 让 Yi - Xi 最大
    // 3. 为了让队头永远是最大值，队列内部点的 Yi - Xi 必须保持严格单调递减
    int* deque = malloc(sizeof(int) * pointsSize);
    int front = 0, rear = 0;
    int res = INF_MIN;

    for (int l = 0, r = 0; r < pointsSize; ++r) {
        // 先缩短 l 并同步队头
        while (points[r][0] - points[l][0] > k) {
            ++l;
            if (deque[front] < l) ++front;
        }

        // 再结算答案
        // 此时由于 l 已经纠偏，[l, r-1] 之间的过期老废料被彻底清空
        // 现在的队头就是绝对安全且最强的合法历史，直接抓来和 r 配对
        if (front < rear) {
            res = MMAX(res, points[r][0] + points[r][1] +
                                points[deque[front]][1] -
                                points[deque[front]][0]);
        }

        // 最后让 r 入队，绝对不能提前
        // 若把入队操作移到循环最上方，会带来致命灾难：
        // 若 r 的 Y-X 极大，入队会踢光所有人，导致自己变成队头
        // 这样在步骤 2 就会变成 r 自己和自己配对，违反 i < j 的题意
        // 因此 r 必须在结算完毕后才作为历史入队
        int cur = points[r][1] - points[r][0];
        while (front < rear &&
               points[deque[rear - 1]][1] - points[deque[rear - 1]][0] <= cur) {
            --rear;
        }
        deque[rear++] = r;
    }

    return res;
}
