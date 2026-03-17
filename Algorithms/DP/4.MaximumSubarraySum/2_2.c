int max(int a, int b) { return a > b ? a : b; }

// 空间优化
int rob(int* nums, int numsSize) {
    int left = 0;
    int mid = 0;
    int right = 0;

    for (int i = 0; i < numsSize; ++i) {
        right = max(mid, left + nums[i]);
        left = mid;
        mid = right;
    }

    return right;
}