#include <vector>

using namespace std;

class Solution{public :
                   // 大于 target 的左边界
                   int binarySearch(vector<int> & ends, int len, int target){int left = 0;
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

// 时间复杂度 O(n * logn)
int lengthOfLIS(vector<int>& nums) {
    int n = nums.size();
    // ends[i] 表示所有长度为 i + 1 的不下降子序列的最小结尾
    // [0, len-1] 是有效区，有效区内的数字非递减
    vector<int> ends(n);
    // len 表示 ends 数组目前的有效区长度
    int len = 0;
    for (int i = 0, pos; i < n; ++i) {
        pos = binarySearch(ends, len, nums[i]);
        if (pos == len) {
            // 找不到就扩充 ends
            ends[len++] = nums[i];
        } else {
            // 找到了就更新成更小的 nums[i]
            ends[pos] = nums[i];
        }
    }
    return len;
}
}
;