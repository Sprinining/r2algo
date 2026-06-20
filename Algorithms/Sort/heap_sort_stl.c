void percolate_up(int* nums, int n, int top, int idx) {
    int val = nums[idx];
    int cur = idx, parent = (cur - 1) / 2;
    while (cur > top && nums[parent] < val) {
        nums[cur] = nums[parent];
        cur = parent;
        parent = (cur - 1) / 2;
    }
    nums[cur] = val;
}

void heapify(int* nums, int n, int idx) {
    int val = nums[idx];
    int cur = idx, lc = 2 * cur + 1;
    while (lc < n) {
        if (lc + 1 < n && nums[lc + 1] > nums[lc]) ++lc;
        nums[cur] = nums[lc];
        cur = lc;
        lc = 2 * cur + 1;
    }
    nums[cur] = val;
    percolate_up(nums, n, idx, cur);
}

void pop(int* nums, int n) {
    int val = nums[0];
    nums[0] = nums[n - 1];
    nums[n - 1] = val;
    heapify(nums, n - 1, 0);
}

int* sortArray(int* nums, int numsSize, int* returnSize) {
    *returnSize = numsSize;
    for (int i = (numsSize - 1) / 2; i >= 0; --i) heapify(nums, numsSize, i);
    for (int len = numsSize; len > 1; --len) pop(nums, len);
    return nums;
}
