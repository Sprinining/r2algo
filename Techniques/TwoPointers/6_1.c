#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define MMAX(a, b) ((a) > (b) ? (a) : (b))
#define ABS(a, b) ((a) > (b) ? (a) - (b) : (b) - (a))

int *houses, *heaters;
int n, m;

int cmp(const void* a, const void* b) {
    int x = *(int*)a;
    int y = *(int*)b;
    if (x > y) return 1;
    if (x < y) return -1;
    return 0;
}

bool best(int i, int j) {
    // 后面没有供暖器了，则当前 j 必选；或者发现接下来的 j+1 供暖器到房屋 i
    // 的距离开始变远了
    return j == m - 1 ||
           ABS(heaters[j], houses[i]) < ABS(heaters[j + 1], houses[i]);
}

int findRadius(int* houses_, int housesSize, int* heaters_, int heatersSize) {
    houses = houses_;
    heaters = heaters_;
    n = housesSize;
    m = heatersSize;

    qsort(houses, n, sizeof(houses[0]), cmp);
    qsort(heaters, m, sizeof(heaters[0]), cmp);

    int res = 0;
    for (int i = 0, j = 0; i < housesSize; ++i) {
        // 如果下一个供暖器 j+1 离当前房屋 i 更近，供暖器指针 j 就不停向右移
        while (!best(i, j)) ++j;
        // 取所有房屋到各自最近供暖器距离的最大值，即为能覆盖全员的最小半径
        res = MMAX(res, ABS(houses[i], heaters[j]));
    }

    return res;
}
