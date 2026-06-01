#include <stdlib.h>

#define MAXN 100005

// 递减栈
int stk[MAXN];
int sz;

int* dailyTemperatures(int* temperatures, int temperaturesSize,
                       int* returnSize) {
    int n = temperaturesSize;
    *returnSize = n;
    int* res = calloc(n, sizeof(int));
    sz = 0;

    for (int i = 0; i < n; ++i) {
        while (sz > 0 && temperatures[stk[sz - 1]] < temperatures[i]) {
            int top = stk[--sz];
            res[top] = i - top;
        }
        stk[sz++] = i;
    }
    return res;
}
