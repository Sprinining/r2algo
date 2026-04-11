#include <stdio.h>
#include <stdlib.h>

int mmax(int a, int b) { return a > b ? a : b; }

int n, k;

// 在降序序列中找到严格小于 target 的第一个位置
int binarySearch1(int* ary, int len, int target) {
    int left = 0;
    int right = len - 1;
    int mid;
    while (left <= right) {
        mid = left + ((right - left) >> 1);
        if (ary[mid] < target) {
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    return left;
}

// 在升序序列中找到严格大于 target 的第一个位置
int binarySearch2(int* ary, int len, int target) {
    int left = 0;
    int right = len - 1;
    int mid;
    while (left <= right) {
        mid = left + ((right - left) >> 1);
        if (ary[mid] > target) {
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    return left;
}

int main() {
    scanf("%d%d", &n, &k);
    int* nums = malloc(sizeof(*nums) * n);
    for (int i = 0; i < n; ++i) scanf("%d", &nums[i]);

    int* ends = malloc(sizeof(*ends) * n);
    int len = 0;

    // rightMaxLen[i] = 必须以 nums[i] 开头的最长不下降子序列长度
    // 不是随便从后面选一个最长的，因为拼接点是 nums[i]，中间区域的 k 个要变成 nums[i]
    // 如果右边区域随便选，可能会选到一个下降的子序列
    int* rightMaxLen = malloc(sizeof(*rightMaxLen) * n);
    for (int i = n - 1; i >= 0; --i) {
        int pos = binarySearch1(ends, len, nums[i]);
        if (pos == len) {
            ends[len++] = nums[i];
            rightMaxLen[i] = len;
        } else {
            ends[pos] = nums[i];
            // 必须以 nums[i] 开头的最长不下降子序列长度
            rightMaxLen[i] = pos + 1;
        }
    }

    // 置零 len，复用 ends
    len = 0;
    int res = 0;
    for (int j = k; j < n; ++j) {
        int i = j - k;
        // 根据拼接点 nums[j] 查，返回左边 LIS 能接到 nums[j] 的最大长度
        int pos = binarySearch2(ends, len, nums[j]);
        res = mmax(res, pos + k + rightMaxLen[j]);
        // 维护下一轮左边 LIS 的状态
        pos = binarySearch2(ends, len, nums[i]);
        if (pos == len) {
            ends[len++] = nums[i];
        } else {
            ends[pos] = nums[i];
        }
    }

    // 特殊情况，最后 k 个全改：相当于 左边 LIS + k
    res = mmax(res, len + k);

    printf("%d", res);
}