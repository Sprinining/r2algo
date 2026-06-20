#include <stdlib.h>

void swap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

void quick_sort(int* nums, int left, int right) {
    if (left >= right) return;

    // 随机选择一个位置，把它和最左边交换
    // 这样就彻底破坏了极端测试用例的针对性
    int rand_idx = left + rand() % (right - left + 1);
    swap(&nums[left], &nums[rand_idx]);
    int pivot = nums[left];
    int l = left, r = right;

    // 挖坑法
    while (l < r) {
        while (l < r && nums[r] >= pivot) --r;
        if (l < r) nums[l++] = nums[r];
        while (l < r && nums[l] <= pivot) ++l;
        if (l < r) nums[r--] = nums[l];
    }
    nums[l] = pivot;

    quick_sort(nums, left, l - 1);
    quick_sort(nums, l + 1, right);
}

int* sortArray(int* nums, int numsSize, int* returnSize) {
    *returnSize = numsSize;
    quick_sort(nums, 0, numsSize - 1);
    return nums;
}
