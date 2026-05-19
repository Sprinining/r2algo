#define MAXL 100000

double heap[MAXL];
int len;

void percolateUp(int top, int idx) {
    double val = heap[idx];
    int cur = idx;
    int parent = (cur - 1) / 2;
    while (cur > top && heap[parent] < val) {
        heap[cur] = heap[parent];
        cur = parent;
        parent = (cur - 1) / 2;
    }
    heap[cur] = val;
}

void heapify(int idx) {
    double val = heap[idx];
    int cur = idx;
    int lc = 2 * cur + 1;
    while (lc < len) {
        if (lc + 1 < len && heap[lc + 1] > heap[lc]) ++lc;
        heap[cur] = heap[lc];
        cur = lc;
        lc = 2 * cur + 1;
    }

    heap[cur] = val;
    percolateUp(idx, cur);
}

void bottomUp() {
    for (int i = len / 2 - 1; i >= 0; --i) heapify(i);
}

double getHalfAndReset() {
    heap[0] /= 2;
    double res = heap[0];
    heapify(0);
    return res;
}

int halveArray(int* nums, int numsSize) {
    double half = 0;
    len = 0;
    for (int i = 0; i < numsSize; ++i) {
        heap[len++] = (double)nums[i];
        half += nums[i];
    }
    half /= 2;

    bottomUp();

    int res = 0;
    for (double sum = 0; sum < half;) {
        sum += getHalfAndReset();
        ++res;
    }

    return res;
}
