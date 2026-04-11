#include <stdlib.h>

int m1n(int a, int b) { return a > b ? b : a; }

int cmp(const void* a, const void* b) {
    int* ea = *(int**)a;
    int* eb = *(int**)b;
    // 根据第一个元素升序排序
    return ea[0] - eb[0];
}

int binarySearch(int* ary, int len, int target) {
    int left = 0;
    int right = len - 1;
    int mid;
    while (left <= right) {
        mid = left + (right - left) / 2;
        if (ary[mid] >= target) {
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    return left;
}

int findLongestChain(int** pairs, int pairsSize, int* pairsColSize) {
    qsort(pairs, pairsSize, sizeof(*pairs), cmp);

    // ends[i] 表示所有长度为 i+1 的递增子序列的最小结尾
    int* ends = malloc(sizeof(*ends) * pairsSize);
    int len = 0;

    for (int i = 0; i < pairsSize; ++i) {
        // 根据第一个数查
        int pos = binarySearch(ends, len, pairs[i][0]);
        // 插入的是第二个数
        if (pos == len) {
            ends[len++] = pairs[i][1];
        } else {
            // 最小结尾
            ends[pos] = m1n(ends[pos], pairs[i][1]);
        }
    }
    return len;
}