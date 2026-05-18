void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// 自上而下调整大顶堆，O(logn)
void heapify(int* nums, int n, int idx) {
    int val = nums[idx];
    // 当前要调整位置，找最终位置的下标
    int cur = idx;
    // 左孩子节点下标
    int lc = idx * 2 + 1;
    while (lc < n) {
        // 如果有右孩子，且右孩子更大，那就把他当作左孩子
        if (lc + 1 < n && nums[lc + 1] > nums[lc]) ++lc;
        if (val >= nums[lc]) break;
        nums[cur] = nums[lc];
        cur = lc;
        lc = 2 * cur + 1;
    }
    nums[cur] = val;
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
