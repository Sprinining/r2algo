#define MMIN(a, b) ((a) > (b) ? (b) : (a))
#define INF_MAX 0x3f3f3f3f

int minSubArrayLen(int target, int* nums, int numsSize) {
    int res = INF_MAX;
    // 以 nums[r] 结尾的子数组是否符合条件
    for (int l = 0, r = 0, sum = 0; r < numsSize; ++r) {
        sum += nums[r];
        // 窗口初始增长中
        if (sum < target) continue;
        // 尽量减小以 nums[r] 结尾的子数组长度
        while (sum - nums[l] >= target) sum -= nums[l++];
        res = MMIN(res, r - l + 1);
    }
    return res == INF_MAX ? 0 : res;
}
