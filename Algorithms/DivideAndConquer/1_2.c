#include <stdlib.h>
#include <string.h>

void merge(int* nums, int left, int mid, int right, int* temp) {
    int p = left;
    int q = mid + 1;
    int idx = 0;

    while (p <= mid && q <= right) {
        if (nums[p] <= nums[q]) {
            temp[idx++] = nums[p++];
        } else {
            temp[idx++] = nums[q++];
        }
    }

    while (p <= mid) temp[idx++] = nums[p++];
    while (q <= right) temp[idx++] = nums[q++];

    memcpy(&nums[left], temp, sizeof(int) * idx);
}

int* sortArray(int* nums, int numsSize, int* returnSize) {
    *returnSize = numsSize;
    if (numsSize <= 1) return nums;

    int* temp = malloc(numsSize * sizeof(int));

    // step 代表当前子数组的长度，每次循环翻倍：1, 2, 4, 8...
    for (int step = 1; step < numsSize; step *= 2) {
        // 按照当前步长，成对遍历并合并子数组
        for (int left = 0; left < numsSize - step; left += 2 * step) {
            int mid = left + step - 1;

            // 计算右边界，防止最后一组的右半部分越界
            int right = left + 2 * step - 1;
            if (right >= numsSize) right = numsSize - 1;

            // 合并 [left, mid] 和 [mid + 1, right]
            merge(nums, left, mid, right, temp);
        }
    }

    return nums;
}
