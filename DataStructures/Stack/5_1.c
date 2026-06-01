#include <stdlib.h>

#define MAXN 205
#define MMAX(a, b) ((a) > (b) ? (a) : (b))

int stk[MAXN];
int sz;

int maximalRectangle(char** matrix, int matrixSize, int* matrixColSize) {
    int n = matrixColSize[0] + 2;
    int* height = calloc(n, sizeof(int));
    // 哨兵
    height[0] = height[n - 1] = -1;

    int res = 0;
    for (int i = 0; i < matrixSize; ++i) {
        // 压缩成一行
        for (int j = 0; j < matrixColSize[0]; ++j)
            height[j + 1] = matrix[i][j] == '0' ? 0 : height[j + 1] + 1;

        sz = 0;
        for (int k = 0; k < n; ++k) {
            while (sz > 0 && height[stk[sz - 1]] > height[k]) {
                int top = stk[--sz];
                int len = k - stk[sz - 1] - 1;
                res = MMAX(res, height[top] * len);
            }
            stk[sz++] = k;
        }
    }

    return res;
}
