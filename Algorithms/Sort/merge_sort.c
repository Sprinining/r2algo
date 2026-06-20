#include <stdlib.h>
#include <string.h>

void merge(int* nums, int left, int mid, int right, int* temp) {
    int p = left, q = mid + 1;
    int idx = 0;
    while (p <= mid && q <= right) {
        if (nums[p] < nums[q]) {
            temp[idx++] = nums[p++];
        } else {
            temp[idx++] = nums[q++];
        }
    }
    while (p <= mid) temp[idx++] = nums[p++];
    while (q <= right) temp[idx++] = nums[q++];
    memcpy(&nums[left], temp, sizeof(int) * idx);
}

void merge_sort(int* nums, int left, int right, int* temp) {
    if (left >= right) return;
    int mid = left + ((right - left) >> 1);
    merge_sort(nums, left, mid, temp);
    merge_sort(nums, mid + 1, right, temp);
    merge(nums, left, mid, right, temp);
}

int* sortArray(int* nums, int numsSize, int* returnSize) {
    *returnSize = numsSize;
    int* temp = malloc(sizeof(int) * numsSize);
    merge_sort(nums, 0, numsSize - 1, temp);
    return nums;
}
