#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

int n, k;

// 求最长不上升子序列长度的二分
// ends[0, len - 1] 为降序，找小于 target 的最左位置
int binarySearch1(vector<int> &ends, int len, int target) {
    int left = 0;
    int right = len - 1;
    int mid;
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

// 求最长不下降子序列长度的二分
// ends[0, len-1] 为升序，找大于 target 的最左位置
int binarySearch2(vector<int> &ends, int len, int target) {
    int left = 0;
    int right = len - 1;
    int mid;
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

// 生成辅助数组 rightMaxLen
// rightMaxLen[i]: 以 nums[i] 开头的最长不下降子序列长度
// 等价于从右往左遍历，以 nums[i] 做结尾的情况下的最长不上升子序列
vector<int> getRightMaxLen(vector<int> &ends, vector<int> &nums) {
    vector<int> rightMaxLen(nums.size());
    int len = 0;
    for (int i = n - 1, pos; i >= 0; i--) {
        pos = binarySearch1(ends, len, nums[i]);
        if (pos == len) {
            // 扩充 endsArr
            ends[len++] = nums[i];
            // 记录长度
            rightMaxLen[i] = len;
        } else {
            ends[pos] = nums[i];
            rightMaxLen[i] = pos + 1;
        }
    }
    return rightMaxLen;
}

int main() {
    cin >> n >> k;
    vector<int> nums;
    nums.resize(n);
    for (int i = 0; i < n; ++i)
        cin >> nums[i];

    // 生成辅助数组
    vector<int> ends(n);
    vector<int> rightMaxLen = getRightMaxLen(ends, nums);

    int len = 0;
    int res = 0;
    for (int i = 0, j = k, pos; j < n; i++, j++) {
        // 根据当前划分点查，划分点左侧连续 k 个位置是要改成 nums[j] 的
        pos = binarySearch2(ends, len, nums[j]);

        // res 由三部分组成
        // 左侧：划分点左侧连续 k 个位置再往前的区域中，长度为 pos 的不下降子序列（最大值小于 nums[j]）
        // 中间：划分点左侧连续 k 个位置
        // 右侧：必须以 nums[j] 开始的不下降子序列的长度
        res = max(res, pos + k + rightMaxLen[j]);

        // 要插入的是 nums[i]，所以要再查找下插入位置
        pos = binarySearch2(ends, len, nums[i]);
        if (pos == len) {
            ends[len++] = nums[i];
        } else {
            ends[pos] = nums[i];
        }
    }
    // 特例：最后 k 个元素都改成左侧不下降子序列的最后一个值
    res = max(res, len + k);
    cout << res;
}