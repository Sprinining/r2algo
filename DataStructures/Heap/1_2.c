// 自上而下调整大顶堆，O(logn)
void adjust(int* nums, int n, int idx) {
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

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// 堆尾插入元素，然后向上调整
void heapInsert(int* nums, int idx) {
    int val = nums[idx];
    int cur = idx;
    int parent = (cur - 1) / 2;
    // cur > 0，不能到根节点还继续循环
    while (cur > 0) {
        if (val <= nums[parent]) break;
        nums[cur] = nums[parent];
        cur = parent;
        parent = (cur - 1) / 2;
    }
    nums[cur] = val;
}

// 自顶向下建堆，O(nlogn)
void topDown(int* nums, int n) {
    for (int i = 0; i < n; ++i) heapInsert(nums, i);
}

int* sortArray(int* nums, int numsSize, int* returnSize) {
    topDown(nums, numsSize);

    for (int i = numsSize - 1; i > 0; --i) {
        swap(&nums[0], &nums[i]);
        adjust(nums, i, 0);
    }

    *returnSize = numsSize;
    return nums;
}
