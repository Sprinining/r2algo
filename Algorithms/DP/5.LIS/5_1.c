#include <stdio.h>
#include <stdlib.h>

// 取最大值
#define MAX(a, b) ((a) > (b) ? (a) : (b))

int n, k;

/*
binarySearch1（右侧用）
在降序数组 ends 中找第一个 < target 的位置
最长不上升子序列（从右往左构造）
*/
int binarySearch1(int* ends, int len, int target) {
    int left = 0, right = len - 1, mid;

    while (left <= right) {
        mid = left + ((right - left) >> 1);
        if (ends[mid] < target) {
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    return left;
}

/*
binarySearch2（左侧用）
在升序数组ends 中找第一个 > target 的位置
最长不下降子序列（LIS变体）
*/
int binarySearch2(int* ends, int len, int target) {
    int left = 0, right = len - 1, mid;

    while (left <= right) {
        mid = left + ((right - left) >> 1);
        if (ends[mid] > target) {
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    return left;
}

/*
rightMaxLen[i] 表示从 i 开始，往右的最长“不下降子序列”长度
转换为：从右往左的“最长不上升子序列”。因为 LIS 通常是“结尾”，但这里要“开头”
*/
int* getRightMaxLen(int* nums, int* ends) {
    int* rightMaxLen = malloc(sizeof(*rightMaxLen) * n);
    // 当前 ends 有效长度
    int len = 0;

    // 从右往左扫
    for (int i = n - 1; i >= 0; --i) {
        // 找插入位置
        int pos = binarySearch1(ends, len, nums[i]);
        if (pos == len) {
            // 扩展最长长度
            ends[len++] = nums[i];
            rightMaxLen[i] = len;
        } else {
            // 替换，保持“更优尾部”
            ends[pos] = nums[i];
            rightMaxLen[i] = pos + 1;
        }
    }

    return rightMaxLen;
}

/*
枚举修改区间的位置
结构：[左边] + [k个修改] + [右边]
左边：最长不下降子序列（结尾 < nums[j]）
中间：k（直接改）
右边：必须从 nums[j] 开始的最长不下降子序列
*/
int main() {
    scanf("%d %d", &n, &k);

    int* nums = malloc(sizeof(*nums) * n);
    for (int i = 0; i < n; ++i) scanf("%d", &nums[i]);
    int* ends = malloc(sizeof(*ends) * n);
    int* rightMaxLen = getRightMaxLen(nums, ends);

    int len = 0;
    int res = 0;
    // 枚举修改区间：左边界 i，右边界 j = i + k
    for (int i = 0, j = k; j < n; i++, j++) {
        // 左边：找一个最长 LIS，使其结尾 <= nums[j]
        int pos = binarySearch2(ends, len, nums[j]);

        // 三段拼接：左边 LIS + k + 右边 LIS
        res = MAX(res, pos + k + rightMaxLen[j]);

        // 把 nums[i] 加入左侧 LIS
        pos = binarySearch2(ends, len, nums[i]);

        if (pos == len) {
            ends[len++] = nums[i];
        } else {
            ends[pos] = nums[i];
        }
    }

    // 特殊情况，最后 k 个全改：相当于 左边 LIS + k
    res = MAX(res, len + k);

    printf("%d\n", res);

    return 0;
}