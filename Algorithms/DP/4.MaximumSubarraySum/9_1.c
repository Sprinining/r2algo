#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MMIN(a, b) ((a) > (b) ? (b) : (a))
#define MMAX(a, b) ((a) > (b) ? (a) : (b))

// 给定一个数组 nums，其中可能有正、负、0
// 每个魔法卷轴可以把 nums 中连续的一段全变成 0
// 卷轴使不使用、使用多少随意，但一共只有2个魔法卷轴，返回数组整体尽可能大的累加和

// 在 [left, right] 上必须用一次卷轴
int mustUseOne(int* nums, int left, int right) {
    int max_res = 0x80000000;
    for (int i = left; i <= right; ++i) {
        for (int j = i; j <= right; ++j) {
            // [i, j] 位置刷成 0
            // 计算其他位置的和
            int sum = 0;
            for (int k = left; k < i; ++k) sum += nums[k];
            for (int k = j + 1; k <= right; ++k) sum += nums[k];
            max_res = MMAX(max_res, sum);
        }
    }
    return max_res;
}

// 暴力解
int func1(int* nums, int numsSize) {
    // 不用
    int p1 = 0;
    for (int i = 0; i < numsSize; ++i) p1 += nums[i];
    // 必须用一次
    int p2 = mustUseOne(nums, 0, numsSize - 1);
    // 必须用两次
    int p3 = 0x80000000;
    for (int i = 0; i < numsSize; ++i) {
        p3 = MMAX(p3, mustUseOne(nums, 0, i) + mustUseOne(nums, i + 1, numsSize - 1));
    }
    return MMAX(p1, MMAX(p2, p3));
}

// 把最小的负数和子数组刷成 0
void change(int* nums, int numsSize) {
    if (numsSize == 1) return;
    int pre = nums[0];
    int min_sum = pre;
    int begin = 0;
    int end = 0;
    for (int i = 0; i < numsSize; ++i) {
        if (pre < 0) {
            pre += nums[i];
        } else {
            pre = nums[i];
            begin = i;
        }
        if (pre < min_sum) {
            min_sum = pre;
            end = i;
        }
    }
    if (min_sum < 0) memset(nums + begin, 0, sizeof(*nums) * (end - begin + 1));
}

// 错误解法：这里的问题结构是两个区间不能重叠，选择第一个区间会影响第二个区间的选择空间，这就破坏了贪心成立条件（无后效性）
// 反例：nums = [5, -100, 6, -100, 5]，func2 会变成 [5, 0, 0, 0, 5]
int func2(int* nums, int numsSize) {
    change(nums, numsSize);  // 第一次就把中间三个变成 0，[5, 0, 0, 0, 5]
    change(nums, numsSize);  // 第二次什么也不变动
    // 实际应该 [5, 0, 6, 0, 5]
    int res = 0;
    for (int i = 0; i < numsSize; ++i) res += nums[i];
    return res;
}

// 保留最大子数组
int func3(int* nums, int numsSize) {
    if (numsSize == 1) return nums[0] < 0 ? 0 : nums[0];

    // 不用卷轴
    int p1 = 0;
    for (int i = 0; i < numsSize; ++i) p1 += nums[i];

    // 左边必须用一次
    // lmax_dp[i] = 在 [0, i] 范围内必须使用一次卷轴能够得到的最大累加和
    int* lmax_dp = (int*)malloc(sizeof(*lmax_dp) * numsSize);
    lmax_dp[0] = nums[0] < 0 ? 0 : nums[0];

    int prefix_sum = nums[0];
    // 0 表示左边全部变成 0
    int max_prefix_sum = MMAX(0, nums[0]);

    for (int i = 1; i < numsSize; ++i) {
        // 情况1：卷轴已经在前面用过了，在 0~i-1 已经删过一段了，所以 nums[i] 只能保留
        // 情况2：卷轴现在才用，卷轴覆盖的是 [l, i]，剩下的是 [0, l-1]
        lmax_dp[i] = MMAX(lmax_dp[i - 1] + nums[i], max_prefix_sum);
        prefix_sum += nums[i];
        max_prefix_sum = MMAX(max_prefix_sum, prefix_sum);
    }

    // 用一次卷轴
    int p2 = lmax_dp[numsSize - 1];

    // 右边必须用一次
    // rmax_dp[i] = 在 [i, numsSize-1] 范围内必须使用一次卷轴能够得到的最大累加和
    int* rmax_dp = (int*)malloc(sizeof(*rmax_dp) * numsSize);
    rmax_dp[numsSize - 1] = nums[numsSize - 1] < 0 ? 0 : nums[numsSize - 1];
    int suffix_sum = nums[numsSize - 1];
    int max_suffix_sum = MMAX(0, nums[numsSize - 1]);
    for (int i = numsSize - 2; i >= 0; --i) {
        rmax_dp[i] = MMAX(rmax_dp[i + 1] + nums[i], max_suffix_sum);
        suffix_sum += nums[i];
        max_suffix_sum = MMAX(max_suffix_sum, suffix_sum);
    }

    // 用两次卷轴
    int p3 = 0x80000000;
    for (int i = 0; i < numsSize - 1; ++i) {
        p3 = MMAX(p3, lmax_dp[i] + rmax_dp[i + 1]);
    }

    return MMAX(p1, MMAX(p2, p3));
}

// 删除最小子数组
int func4(int* nums, int numsSize) {
    int total = 0;
    for (int i = 0; i < numsSize; ++i) total += nums[i];

    // lmin_dp[i] = 在 [0, i] 范围内的最小累加和
    int* lmin_dp = (int*)malloc(sizeof(*lmin_dp) * numsSize);
    lmin_dp[0] = nums[0];
    int pre = nums[0];
    for (int i = 1; i < numsSize; ++i) {
        // pre = pre > 0 ? nums[i] : pre + nums[i];
        pre = MMIN(nums[i], pre + nums[i]);
        lmin_dp[i] = MMIN(lmin_dp[i - 1], pre);
    }

    int* rmin_dp = (int*)malloc(sizeof(*rmin_dp) * numsSize);
    rmin_dp[numsSize - 1] = nums[numsSize - 1];
    pre = nums[numsSize - 1];
    for (int i = numsSize - 2; i >= 0; --i) {
        pre = MMIN(nums[i], pre + nums[i]);
        rmin_dp[i] = MMIN(rmin_dp[i + 1], pre);
    }

    int p1 = total;
    int p2 = total - lmin_dp[numsSize - 1];
    int p3 = 0x80000000;
    for (int i = 0; i < numsSize - 1; ++i) {
        p3 = MMAX(p3, total - lmin_dp[i] - rmin_dp[i + 1]);
    }

    return MMAX(p1, MMAX(p2, p3));
}

bool judge() {
    int numsSize = 100;
    int* nums = (int*)malloc(sizeof(*nums) * numsSize);
    // 测试用例需要有负数
    // [-100, 100]
    for (int i = 0; i < numsSize; ++i) nums[i] = rand() % 201 - 100;

    int r1 = func1(nums, numsSize);
    int r3 = func3(nums, numsSize);
    int r4 = func4(nums, numsSize);
    if (r1 != r3 || r3 != r4) {
        printf("error: %d %d %d\n", r1, r3, r4);
        return false;
    }
    return true;
}

int main() {
    srand(time(NULL));
    int trials = 100;
    for (int i = 0; i < trials; ++i) {
        if (!judge()) exit(EXIT_FAILURE);
    }
    printf("all success\n");
}