#include <stdlib.h>

int cmp(const void* a, const void* b) {
    int* ea = *(int**)a;
    int* eb = *(int**)b;
    // 根据第二个元素升序排序
    return ea[1] - eb[1];
}

// 区间最多不重叠问题，直接贪心，按结束时间排序一定最优，结束越早，对未来限制越小
int findLongestChain(int** pairs, int pairsSize, int* pairsColSize) {
    qsort(pairs, pairsSize, sizeof(*pairs), cmp);

    int pre = -1001;
    int res = 0;

    for (int i = 0; i < pairsSize; ++i) {
        if (pre < pairs[i][0]) {
            pre = pairs[i][1];
            res++;
        }
    }
    return res;
}