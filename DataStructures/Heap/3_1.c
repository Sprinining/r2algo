#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define MAXN 10000
#define MMAX(a, b) ((a) > (b) ? (a) : (b))

int cmp(const void* a, const void* b) {
    int* x = (int*)a;
    int* y = (int*)b;
    if (x[0] < y[0]) return -1;
    if (x[0] > y[0]) return 1;
    return 0;
}

void swap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

int n;
int line[MAXN][2];
// 小根堆，存放线段右端点
int heap[MAXN];
int len;

// 上浮调整
void percolate(int top, int idx) {
    int val = heap[idx];
    int cur = idx;
    int parent = (cur - 1) / 2;
    while (cur > top && heap[parent] > val) {
        heap[cur] = heap[parent];
        cur = parent;
        parent = (cur - 1) / 2;
    }
    heap[cur] = val;
}

void heapify(int idx) {
    int val = heap[idx];
    int cur = idx;
    int lc = 2 * cur + 1;
    while (lc < len) {
        if (lc + 1 < len && heap[lc + 1] < heap[lc]) ++lc;
        heap[cur] = heap[lc];
        cur = lc;
        lc = 2 * cur + 1;
    }
    heap[cur] = val;
    percolate(idx, cur);
}

void popHeap() {
    swap(&heap[0], &heap[--len]);
    heapify(0);
}

void pushHeap(int val) {
    heap[len++] = val;
    percolate(0, len - 1);
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) scanf("%d%d", &line[i][0], &line[i][1]);

    // 根据线段起点升序排序
    qsort(line, n, sizeof(line[0]), cmp);

    len = 0;
    int res = 0;
    for (int i = 0; i < n; ++i) {
        int start = line[i][0];
        int end = line[i][1];
        // 如果一个线段的右端点没超过当前线段左端点，就不会有重合位置，全都出堆
        while (len > 0 && heap[0] <= start) popHeap();
        pushHeap(end);
        // 堆中剩下的线段都会和当前线段有重合
        res = MMAX(res, len);
    }

    printf("%d\n", res);
    return 0;
}
