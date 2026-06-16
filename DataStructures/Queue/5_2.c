#include <stdlib.h>

#define MMAX(a, b) ((a) > (b) ? (a) : (b))
#define INF_MIN -0x3f3f3f3f

int findMaxValueOfEquation(int** points, int pointsSize, int* pointsColSize,
                           int k) {
    int* deque = malloc(sizeof(int) * pointsSize);
    int front = 0, rear = 0;
    int res = INF_MIN;

    for (int r = 0; r < pointsSize; ++r) {
        while (front < rear && points[r][0] - points[deque[front]][0] > k)
            ++front;

        if (front < rear) {
            res = MMAX(res, points[r][0] + points[r][1] +
                                points[deque[front]][1] -
                                points[deque[front]][0]);
        }

        int cur = points[r][1] - points[r][0];
        while (front < rear &&
               points[deque[rear - 1]][1] - points[deque[rear - 1]][0] <= cur) {
            --rear;
        }
        deque[rear++] = r;
    }

    return res;
}
