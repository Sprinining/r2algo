int* sortArray(int* nums, int numsSize, int* returnSize) {
    *returnSize = numsSize;
    for (int i = 1; i < numsSize; ++i) {
        int cur = nums[i];
        int j = i;
        while (j > 0 && nums[j - 1] > cur) {
            nums[j] = nums[j - 1];
            --j;
        }
        nums[j] = cur;
    }
    return nums;
}
