#include <stdlib.h>

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

// 最长不下降子序列
int kIncreasing(int* arr, int arrSize, int k) {
    int max_len = arrSize / k + 1;
    int* ends = malloc(sizeof(*ends) * max_len);
    int len;

    int sum = 0;
    // 分组
    for (int t = 0; t < k; ++t) {
        // 每组的最长不下降子序列长度
        len = 0;
        for (int i = t; i < arrSize; i += k) {
            int pos = binarySearch(ends, len, arr[i]);
            if (pos == len) {
                ends[len++] = arr[i];
            } else {
                ends[pos] = arr[i];
            }
        }
        sum += len;
    }
    return arrSize - sum;
}