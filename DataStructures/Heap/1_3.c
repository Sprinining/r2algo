void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// 上浮
void percolateUp(int* nums, int top, int idx) {
    int val = nums[idx];
    int cur = idx;
    int parent = (cur - 1) / 2;
    while (cur > top && val > nums[parent]) {
        nums[cur] = nums[parent];
        cur = parent;
        parent = (cur - 1) / 2;
    }
    nums[cur] = val;
}

// 自上而下调整大顶堆，O(logn)
void heapify(int* nums, int n, int idx) {
    int val = nums[idx];
    int cur = idx;
    int lc = idx * 2 + 1;
    // 盲目下沉到叶子节点，不与 val 进行比较
    while (lc < n) {
        if (lc + 1 < n && nums[lc + 1] > nums[lc]) ++lc;
        nums[cur] = nums[lc];
        cur = lc;
        lc = 2 * cur + 1;
    }
    nums[cur] = val;

    // 进行一次上浮操作，找到最终位置
    percolateUp(nums, idx, cur);
}

// 自底向上建堆，O(n)
void bottomUp(int* nums, int n) {
    // 从最后一个非叶子节点开始往上
    for (int i = (n - 1) / 2; i >= 0; --i) heapify(nums, n, i);
}

int* sortArray(int* nums, int numsSize, int* returnSize) {
    bottomUp(nums, numsSize);

    for (int i = numsSize - 1; i > 0; --i) {
        swap(&nums[0], &nums[i]);
        heapify(nums, i, 0);
    }

    *returnSize = numsSize;
    return nums;
}
