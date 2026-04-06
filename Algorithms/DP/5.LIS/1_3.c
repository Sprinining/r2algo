#include <stdio.h>
#include <stdlib.h>

// 最长不下降子序列
// 大于等于 target 的左边界
int binarySearch(int* arr, int len, int target) {
    int left = 0;
    int right = len - 1;
    int mid;
    while (left <= right) {
        mid = left + (right - left) / 2;
        if (arr[mid] > target) {
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    return left;
}

// 时间复杂度 O(n * logn)
int lengthOfLIS(int* nums, int numsSize) {
    // ends[i] 表示所有长度为 i+1 的递增子序列的最小结尾
    int* ends = malloc(sizeof(*ends) * numsSize);
    // [0, len-1] 是有效区，有效区内的数字一定严格升序
    int len = 0;
    for (int i = 0; i < numsSize; ++i) {
        int pos = binarySearch(ends, len, nums[i]);
        if (pos == len) {
            // 找不到就扩充 ends
            ends[len++] = nums[i];
        } else {
            // 找到了就更新成更小的 nums[i]
            // 同样长度的递增子序列，结尾越小越好，后面更容易接后续元素
            ends[pos] = nums[i];
        }
    }
    return len;
}