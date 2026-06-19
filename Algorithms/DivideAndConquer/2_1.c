#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 返回 nums[left, right] 上大于等于 target 的数字个数
// 找大于等于 target 的最左位置
int binary_search(int* nums, int left, int right, int target) {
    int l = left, r = right;
    int m;
    while (l <= r) {
        m = l + ((r - l) >> 1);
        if (nums[m] >= target) {
            r = m - 1;
        } else {
            l = m + 1;
        }
    }
    return right - l + 1;
}

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

// 归并排序的同时计算小和
// O(Nlog^2N)
long long divide(int* nums, int left, int right, int* temp) {
    if (left == right) return 0;

    int mid = left + ((right - left) >> 1);
    long long res = 0;

    // 左侧小和
    res += divide(nums, left, mid, temp);
    // 右侧小和
    res += divide(nums, mid + 1, right, temp);
    // 跨越左右产生的小和
    for (int i = left; i <= mid; ++i)
        res +=
            (long long)nums[i] * binary_search(nums, mid + 1, right, nums[i]);

    // 合并
    merge(nums, left, mid, right, temp);

    return res;
}

int main() {
    int n;
    scanf("%d", &n);
    int* nums = malloc(sizeof(int) * n);
    for (int i = 0; i < n; ++i) scanf("%d", &nums[i]);

    int* temp = malloc(sizeof(int) * n);
    printf("%lld", divide(nums, 0, n - 1, temp));

    return 0;
}
