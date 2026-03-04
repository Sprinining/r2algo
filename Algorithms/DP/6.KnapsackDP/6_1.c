#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAXN 15
#define MAXS (1 << MAXN)  // 最大子序列数
#define MAXK (1 << MAXN)  // k 最大值

/* =========================================================
   工具函数
   ========================================================= */

int cmp_ll(const void* a, const void* b) {
    long long x = *(long long*)a;
    long long y = *(long long*)b;
    if (x < y) return -1;
    if (x > y) return 1;
    return 0;
}

int cmp_int(const void* a, const void* b) { return (*(int*)a) - (*(int*)b); }

int equals(long long a[], long long b[], int k) {
    for (int i = 0; i < k; i++)
        if (a[i] != b[i]) return 0;
    return 1;
}

/* =========================================================
   一、暴力
   ========================================================= */

long long allSums[MAXS];
int sumSize;

void dfs(int nums[], int n, int idx, long long cur) {
    if (idx == n) {
        allSums[sumSize++] = cur;
        return;
    }
    dfs(nums, n, idx + 1, cur);
    dfs(nums, n, idx + 1, cur + nums[idx]);
}

void topKSum_brutal(int nums[], int n, int k, long long result[]) {
    sumSize = 0;
    dfs(nums, n, 0, 0);
    qsort(allSums, sumSize, sizeof(long long), cmp_ll);
    for (int i = 0; i < k; i++) result[i] = allSums[i];
}

/* =========================================================
   二、01背包
   ========================================================= */

void topKSum_dp(int nums[], int n, int k, long long result[]) {
    int total = 0;
    for (int i = 0; i < n; i++) total += nums[i];

    long long* dp = (long long*)calloc(total + 1, sizeof(long long));
    dp[0] = 1;

    for (int i = 0; i < n; i++)
        for (int j = total; j >= nums[i]; j--) dp[j] += dp[j - nums[i]];

    int idx = 0;
    for (int j = 0; j <= total && idx < k; j++)
        while (dp[j] > 0 && idx < k) {
            result[idx++] = j;
            dp[j]--;
        }

    free(dp);
}

/* =========================================================
   三、堆优化
   ========================================================= */

typedef struct {
    int index;
    long long sum;
} Node;

Node heap[MAXK * 2];
int heapSize;

void swap(Node* a, Node* b) {
    Node t = *a;
    *a = *b;
    *b = t;
}

void heapPush(Node x) {
    heap[heapSize] = x;
    int i = heapSize++;
    while (i > 0) {
        int p = (i - 1) / 2;
        if (heap[p].sum <= heap[i].sum) break;
        swap(&heap[p], &heap[i]);
        i = p;
    }
}

Node heapPop() {
    Node ans = heap[0];
    heap[0] = heap[--heapSize];

    int i = 0;
    while (1) {
        int l = i * 2 + 1;
        int r = i * 2 + 2;
        int s = i;

        if (l < heapSize && heap[l].sum < heap[s].sum) s = l;
        if (r < heapSize && heap[r].sum < heap[s].sum) s = r;

        if (s == i) break;

        swap(&heap[i], &heap[s]);
        i = s;
    }
    return ans;
}

void topKSum_heap(int nums[], int n, int k, long long result[]) {
    qsort(nums, n, sizeof(int), cmp_int);

    heapSize = 0;
    result[0] = 0;

    if (n == 0) return;

    Node first = {0, nums[0]};
    heapPush(first);

    for (int i = 1; i < k; i++) {
        if (heapSize == 0) break;

        Node cur = heapPop();
        result[i] = cur.sum;

        int idx = cur.index;
        if (idx + 1 < n) {
            Node replace = {idx + 1, cur.sum - nums[idx] + nums[idx + 1]};
            Node append = {idx + 1, cur.sum + nums[idx + 1]};
            heapPush(replace);
            heapPush(append);
        }
    }
}

/* =========================================================
   主测试
   ========================================================= */

int main() {
    srand((unsigned)time(NULL));

    int testTime = 5000;

    printf("test start\n");

    for (int t = 0; t < testTime; t++) {
        int n = rand() % MAXN + 1;

        int nums[MAXN];
        for (int i = 0; i < n; i++) nums[i] = rand() % 40 + 1;

        int totalSubset = 1 << n;
        int k = rand() % totalSubset + 1;

        long long r1[MAXK] = {0};
        long long r2[MAXK] = {0};
        long long r3[MAXK] = {0};

        topKSum_brutal(nums, n, k, r1);
        topKSum_dp(nums, n, k, r2);
        topKSum_heap(nums, n, k, r3);

        if (!equals(r1, r2, k) || !equals(r1, r3, k)) {
            printf("error!\n");
            return 0;
        }
    }

    printf("test end, all pass!\n");

    return 0;
}