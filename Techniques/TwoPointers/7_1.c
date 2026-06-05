void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// 原地映射：把值为 value 的元素映射到数组中下标为 value-1 的位置
int firstMissingPositive(int* nums, int numsSize) {
    for (int i = 0; i < numsSize; ++i) {
        // 如果 nums[i] 能够映射到数组中
        // 并且它现在所处的目标位置上的值不等于它本身
        // 则通过交换把它送到正确的位置，并继续检查新交换过来的值
        while (nums[i] > 0 && nums[i] <= numsSize &&
               nums[nums[i] - 1] != nums[i]) {
            swap(&nums[nums[i] - 1], &nums[i]);
        }
    }

    // 遍历寻找第一个空缺
    for (int i = 0; i < numsSize; ++i) {
        if (nums[i] != i + 1) return i + 1;
    }

    // 重新映射后，数组中没有空缺，说明缺失的第一个正数就是 numsSize + 1
    return numsSize + 1;
}
