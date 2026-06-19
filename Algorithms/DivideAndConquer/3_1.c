#include <stdlib.h>
#include <string.h>

void merge(int* nums, int left, int mid, int right, int* temp) {
    int p = left, q = mid + 1;
    int idx = 0;
    // 由于判定条件 nums[p] > 2 * nums[q]
    // 和合并条件 nums[p] <= nums[q] 标准不一致
    // 必须将“统计”和“合并”拆分成两个独立的步骤
    // 在合并之前，先用双指针把当前区间的翻转对统计完
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

int divide(int* nums, int left, int right, int* temp) {
    if (left >= right) return 0;
    int mid = left + ((right - left) >> 1);
    int l_cnt = divide(nums, left, mid, temp);
    int r_cnt = divide(nums, mid + 1, right, temp);
    int m_cnt = 0;
    // 双指针
    for (int l = left, r = mid + 1; r <= right; ++r) {
        while (l <= mid && (long long)nums[l] <= 2ll * nums[r]) ++l;
        // 结算与 nums[r] 相关的翻转对
        if (l <= mid) m_cnt += mid - l + 1;
    }
    merge(nums, left, mid, right, temp);
    return l_cnt + m_cnt + r_cnt;
}

int reversePairs(int* nums, int numsSize) {
    int* temp = malloc(sizeof(int) * numsSize);
    return divide(nums, 0, numsSize - 1, temp);
}
