#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
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

    int findLongestChain(vector<vector<int>> &pairs) {
        // 按照数对中第一个数增序
        sort(begin(pairs), end(pairs),
             [](vector<int> &v1, vector<int> &v2) {
                 return v1[0] < v2[0];
             });
        int n = pairs.size();
        vector<int> ends(n);
        int len = 0;
        for (int i = 0, pos; i < n; ++i) {
            // 根据数对中第一个数字查
            pos = binarySearch(ends, len, pairs[i][0]);
            if (pos == len) {
                // 插入的是数对中的第二个数字
                ends[len++] = pairs[i][1];
            } else {
                // 改成较小的
                ends[pos] = min(ends[pos], pairs[i][1]);
            }
        }
        return len;
    }
};