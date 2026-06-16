#include <stdio.h>
#include <stdlib.h>

#define MMIN(a, b) ((a) > (b) ? (b) : (a))
#define INF_MAX 0x3f3f3f3f

int cmp(const void* a, const void* b) {
    int* x = (int*)a;
    int* y = (int*)b;
    if (x[0] < y[0]) return -1;
    if (x[0] > y[0]) return 1;
    return 0;
}

int main() {
    int n, d;
    scanf("%d%d", &n, &d);
    int (*rains)[2] = malloc(sizeof(rains[0]) * n);
    for (int i = 0; i < n; ++i) scanf("%d%d", &(rains[i][0]), &(rains[i][1]));

    qsort(rains, n, sizeof(rains[0]), cmp);

    // 递减，队头最大
    int* deque1 = malloc(sizeof(int) * n);
    int f1 = 0, r1 = 0;
    // 递增，队头最小
    int* deque2 = malloc(sizeof(int) * n);
    int f2 = 0, r2 = 0;

    int res = INF_MAX;
    for (int l = 0, r = 0; r < n; ++r) {
        // 入队
        while (f1 < r1 && rains[deque1[r1 - 1]][1] <= rains[r][1]) --r1;
        deque1[r1++] = r;
        while (f2 < r2 && rains[deque2[r2 - 1]][1] >= rains[r][1]) --r2;
        deque2[r2++] = r;

        // 出队
        while (rains[deque1[f1]][1] - rains[deque2[f2]][1] >= d) {
            res = MMIN(res, rains[r][0] - rains[l][0]);
            ++l;
            if (deque1[f1] < l) ++f1;
            if (deque2[f2] < l) ++f2;
        }
    }

    printf("%d\n", res == INF_MAX ? -1 : res);

    return 0;
}
