#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 归并的同时计算小和
long long merge_and_count(int* nums, int left, int mid, int right, int* temp) {
    int p = left, q = mid + 1;
    int idx = 0;
    long long res = 0;

    while (p <= mid && q <= right) {
        // 如果左侧元素 <= 右侧元素
        // 既然右半部分已经有序，那么右半部分从 q 开始直到 right 的所有元素都 >=
        // nums[p]
        if (nums[p] <= nums[q]) {
            // 直接通过下标计算出满足条件的个数，省去二分查找
            res += (long long)nums[p] * (right - q + 1);
            temp[idx++] = nums[p++];
        } else {
            temp[idx++] = nums[q++];
        }
    }

    // 处理剩余的元素
    while (p <= mid) temp[idx++] = nums[p++];
    while (q <= right) temp[idx++] = nums[q++];

    // 将排好序的元素拷贝回原数组
    memcpy(&nums[left], temp, sizeof(int) * idx);

    return res;
}

// 归并排序分治主体
// O(N*logN)
long long divide(int* nums, int left, int right, int* temp) {
    if (left >= right) return 0;

    int mid = left + ((right - left) >> 1);
    long long res = 0;

    // 累加左半部分、右半部分内部的小和
    res += divide(nums, left, mid, temp);
    res += divide(nums, mid + 1, right, temp);

    // 累加跨越左右边界产生的小和，并执行合并排序
    res += merge_and_count(nums, left, mid, right, temp);

    return res;
}

int main() {
    int n;
    scanf("%d", &n);
    int* nums = malloc(sizeof(int) * n);
    for (int i = 0; i < n; ++i) scanf("%d", &nums[i]);

    int* temp = malloc(sizeof(int) * n);
    // 输出最终的小和结果
    printf("%lld\n", divide(nums, 0, n - 1, temp));

    return 0;
}
