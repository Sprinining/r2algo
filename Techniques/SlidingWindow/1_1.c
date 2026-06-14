#define MMIN(a, b) ((a) > (b) ? (b) : (a))
#define INF_MAX 0x3f3f3f3f

int minSubArrayLen(int target, int* nums, int numsSize) {
    int res = INF_MAX;
    // 以 nums[r] 结尾的子数组是否符合条件
    for (int l = 0, r = 0, sum = 0; r < numsSize; ++r) {
        sum += nums[r];
        // 尽量减小以 nums[r] 结尾的子数组长度
        while (sum >= target) {
            res = MMIN(res, r - l + 1);
            sum -= nums[l++];
        }
    }
    return res == INF_MAX ? 0 : res;
}
