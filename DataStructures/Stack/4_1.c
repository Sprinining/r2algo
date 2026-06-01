#include <stdlib.h>
#include <string.h>

#define MAXN 100005
#define MMAX(a, b) ((a) > (b) ? (a) : (b))

int stk[MAXN];
int sz;

int largestRectangleArea(int* heights, int heightsSize) {
    int n = heightsSize + 2;
    int* arr = malloc(sizeof(int) * n);
    // 哨兵
    arr[0] = arr[n - 1] = -1;
    memcpy(arr + 1, heights, sizeof(int) * heightsSize);

    sz = 0;
    int res = 0;
    for (int i = 0; i < n; ++i) {
        while (sz > 0 && arr[stk[sz - 1]] > arr[i]) {
            int top = stk[--sz];
            // i 是右侧最近的一个更小位置
            // stk[sz-1] 是左侧最近的一个小于等于的位置
            // 栈中会有相同的元素压在相邻位置，最下面的一个出栈时可以正确结算
            int len = i - stk[sz - 1] - 1;
            res = MMAX(res, arr[top] * len);
        }
        stk[sz++] = i;
    }

    return res;
}
