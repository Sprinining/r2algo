#include <stdbool.h>

void swap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

int* sortArray(int* nums, int numsSize, int* returnSize) {
    *returnSize = numsSize;
    for (int i = numsSize - 1; i >= 1; --i) {
        bool is_sorted = true;
        for (int j = 1; j <= i; ++j) {
            if (nums[j - 1] > nums[j]) {
                is_sorted = false;
                swap(&nums[j - 1], &nums[j]);
            }
        }
        if (is_sorted) return nums;
    }
    return nums;
}
