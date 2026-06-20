void swap(int* a, int* b) {
    if (a == b) return;
    int t = *a;
    *a = *b;
    *b = t;
}

int* sortArray(int* nums, int numsSize, int* returnSize) {
    *returnSize = numsSize;
    for (int i = 0; i < numsSize; ++i) {
        int idx = i;
        for (int j = i + 1; j < numsSize; ++j) {
            if (nums[j] < nums[idx]) idx = j;
        }
        swap(&nums[i], &nums[idx]);
    }
    return nums;
}
