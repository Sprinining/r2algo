#include <stdio.h>
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

// 返回小和，且把数组这一段变成有序
// O(NlogN)
long long divide(int* arr, int left, int right, int* temp) {
    if (left >= right) return 0;

    int mid = left + ((right - left) >> 1);

    // 1. 分别计算两侧的小和，并让两侧变得有序
    long long left_sum = divide(arr, left, mid, temp);
    long long right_sum = divide(arr, mid + 1, right, temp);

    // 2. 双指针单向滑动，计算跨越左右边界的小和
    long long mid_sum = 0;
    // 用于持续累加左侧符合条件的元素之和
    long long sum = 0;

    // 遍历右半区，由于右半区单调递增，左指针 l 只需一直向右推进，不需要回退
    for (int l = left, r = mid + 1; r <= right; ++r) {
        while (l <= mid && arr[l] <= arr[r]) sum += arr[l++];
        // 结算与 nums[r] 相关的小和
        mid_sum += sum;
    }

    // 3. 将左右两部分进行合并排序
    merge(arr, left, mid, right, temp);

    return left_sum + mid_sum + right_sum;
}

int main() {
    int n;
    scanf("%d", &n);
    int* nums = (int*)malloc(sizeof(int) * n);
    for (int i = 0; i < n; ++i) scanf("%d", &nums[i]);

    int* temp = (int*)malloc(sizeof(int) * n);
    printf("%lld\n", divide(nums, 0, n - 1, temp));

    return 0;
}
