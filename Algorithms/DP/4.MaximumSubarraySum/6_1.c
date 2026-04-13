#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int* getMaxMatrix(int** matrix, int matrixSize, int* matrixColSize, int* returnSize) {
    int rows = matrixSize;
    int cols = matrixColSize[0];
    *returnSize = 4;
    int* res = malloc(sizeof(*res) * 4);
    int* sums = malloc(sizeof(*sums) * cols);
    int maxSum = 0x80000000;

    // 子矩阵横跨 i1~i2 行
    for (int i1 = 0; i1 < rows; ++i1) {
        // 清空 sums，为后续把每一列的 i1~i2 行压缩成 sums 中的一项做准备
        memset(sums, 0, sizeof(*sums) * cols);
        for (int i2 = i1; i2 < rows; ++i2) {
            // 空间压缩版的子数组最大累加和
            for (int j = 0, pre = 0, begin = 0; j < cols; ++j) {
                // 压缩成 sums[j]
                sums[j] += matrix[i2][j];
                if (pre > 0) {
                    pre += sums[j];
                } else {
                    pre = sums[j];
                    begin = j;
                }
                if (pre >= maxSum) {
                    maxSum = pre;
                    res[0] = i1;
                    res[1] = begin;
                    res[2] = i2;
                    res[3] = j;
                }
            }
        }
    }

    return res;
}