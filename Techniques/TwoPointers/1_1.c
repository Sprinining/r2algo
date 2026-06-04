void swap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

int* sortArrayByParityII(int* nums, int numsSize, int* returnSize) {
    for (int l = 0, r = 1; l < numsSize && r < numsSize; l += 2, r += 2) {
        while (l < numsSize && nums[l] % 2 == 0) l += 2;
        while (r < numsSize && nums[r] % 2 == 1) r += 2;
        if (l < numsSize && r < numsSize) swap(&nums[l], &nums[r]);
    }
    *returnSize = numsSize;
    return nums;
}
