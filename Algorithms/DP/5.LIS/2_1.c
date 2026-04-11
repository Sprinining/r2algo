#include <stdio.h>
#include <stdlib.h>

int cmp(const void* a, const void* b) {
    // a、b 是“数组元素的地址”，这里元素类型是 int*
    // 所以 a、b 的实际类型是 int**
    int* ea = *(int**)a;
    int* eb = *(int**)b;
    // 第一关键字：按宽升序
    if (ea[0] != eb[0]) return ea[0] - eb[0];
    // 第二关键字：宽相同时按高降序
    // 这样可以避免宽相同的信封在后续 LIS 中被错误选中
    return eb[1] - ea[1];
}

// 大于等于 target 的左边界
// 而不是严格大于 target 的左边界，避免 ends 中出现相同的高度
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

int maxEnvelopes(int** envelopes, int envelopesSize, int* envelopesColSize) {
    qsort(envelopes, envelopesSize, sizeof(int*), cmp);

    // ends[i] 表示所有长度为 i+1 的递增子序列的最小结尾
    int* ends = malloc(sizeof(*ends) * envelopesSize);
    int len = 0;

    for (int i = 0; i < envelopesSize; ++i) {
        int num = envelopes[i][1];
        int pos = binarySearch(ends, len, num);
        if (pos == len) {
            // 扩展序列
            ends[len++] = num;
        } else {
            // 更新更优的结尾（更小）
            ends[pos] = num;
        }
    }

    return len;
}
