#include <stdlib.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))

int numSubmat(int** mat, int matSize, int* matColSize) {
    if (matSize == 0 || matColSize[0] == 0) return 0;

    int rows = matSize;
    int columns = matColSize[0];
    int res = 0;

    // 分配高度数组和栈空间
    int* height = calloc(columns, sizeof(int));
    int* stk = malloc(columns * sizeof(int));

    for (int i = 0; i < rows; ++i) {
        // 1. 压缩数组：更新当前行及以上的连续 1 的高度
        for (int j = 0; j < columns; ++j) {
            height[j] = (mat[i][j] == 1) ? height[j] + 1 : 0;
        }

        // 2. 利用单调栈（每个位置存储列索引）计算以当前行为底的子矩阵数量
        int top = -1;  // 初始化/清空栈
        for (int j = 0; j < columns; ++j) {
            while (top != -1 && height[stk[top]] >= height[j]) {
                int cur = stk[top--];  // 弹出栈顶

                // 只有严格大于当前高度才结算；若相等则不结算，等后面位置弹出时一并计算
                if (height[cur] > height[j]) {
                    int left = (top == -1) ? -1 : stk[top];
                    int len = j - left - 1;
                    int bottom = MAX(left == -1 ? 0 : height[left], height[j]);

                    res += (height[cur] - bottom) * len * (len + 1) / 2;
                }
            }
            stk[++top] = j;  // 当前位置压入栈
        }

        // 3. 处理遍历结束后栈中残留的元素
        while (top != -1) {
            int cur = stk[top--];
            int left = (top == -1) ? -1 : stk[top];
            int len = columns - left - 1;
            int down = (left == -1 ? 0 : height[left]);

            res += (height[cur] - down) * len * (len + 1) / 2;
        }
    }

    return res;
}
