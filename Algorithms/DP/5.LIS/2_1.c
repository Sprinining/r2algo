#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

class Solution {
public:
    // 找大于等于的左边界
    int binarySearch(vector<int> &ends, int len, int target) {
        int left = 0;
        int right = len - 1;
        int mid;
        while (left <= right) {
            mid = left + ((right - left) >> 1);
            if (ends[mid] >= target) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        return left;
    }

    int maxEnvelopes(vector<vector<int>> &envelopes) {
        // 宽度从小到大，宽度一样，高度从大到小
        sort(begin(envelopes), end(envelopes),
             [](vector<int> &v1, vector<int> &v2) {
                 return v1[0] == v2[0] ? v1[1] > v2[1] : v1[0] < v2[0];
             });

        int n = envelopes.size();
        // ends[i] 表示长度为 i + 1 的子序列的最小末尾元素
        // 在有效区内严格递增
        vector<int> ends(n);
        // ends 数组的有效长度
        int len = 0;

        for (int i = 0, pos; i < n; ++i) {
            int target = envelopes[i][1];
            pos = binarySearch(ends, len, target);
            if (pos == len) {
                // 找不到就扩充 ends
                ends[len++] = target;
            } else {
                // 找到了就更新成更小的 nums[i]
                ends[pos] = target;
            }
        }

        return len;
    }
};