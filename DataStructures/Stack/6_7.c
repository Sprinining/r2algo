#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAXN 50005
#define MMAX(a, b) ((a) > (b) ? (a) : (b))

// ==================== 方法 1：单调栈（对数器） ====================
int stk[MAXN];
int sz;

int maxWidthRamp_Stack(int* nums, int numsSize) {
    int n = numsSize;
    sz = 0;

    // 递减栈，栈中放着可能的起始位置
    for (int i = 0; i < n; ++i) {
        if (sz == 0 || nums[stk[sz - 1]] > nums[i]) {
            stk[sz++] = i;
        }
    }

    int res = 0;
    for (int i = n - 1; i >= 0; --i) {
        while (sz > 0 && nums[stk[sz - 1]] <= nums[i]) {
            res = MMAX(res, i - stk[sz - 1]);
            --sz;
        }
    }
    return res;
}

// ==================== 方法 2：动态规划（待测方法） ====================
int maxWidthRamp_DP(int* nums, int numsSize) {
    int n = numsSize;
    int* dp = malloc(sizeof(int) * n);

    for (int i = n - 1; i >= 0; --i) {
        dp[i] = 0;
        for (int j = i + 1; j < n; ++j) {
            if (nums[i] <= nums[j]) {
                dp[j] = j - i;
            } else {
                // 依赖左边和原本的值（代表下方）
                int left = (j - 1 >= 0) ? dp[j - 1] : 0;
                dp[j] = MMAX(dp[j], left);
            }
        }
    }

    return dp[n - 1];
}

// ==================== 对数器测试逻辑 ====================

// 生成指定范围内的随机整数
int getRandom(int min, int max) { return min + rand() % (max - min + 1); }

// 打印数组（用于出错时排查）
void printArray(int* arr, int size) {
    printf("[");
    for (int i = 0; i < size; i++) {
        printf("%d", arr[i]);
        if (i < size - 1) printf(", ");
    }
    printf("]\n");
}

int main() {
    // 设置随机数种子
    srand((unsigned int)time(NULL));

    int testTimes = 500;  // 测试轮数
    printf("开始对数器测试，共 %d 轮...\n", testTimes);
    printf("提示要求范围：长度 2~50000，数值 0~50000\n\n");

    int success = 1;
    for (int t = 1; t <= testTimes; t++) {
        // 1. 随机生成符合要求的数组长度 (2 <= length <= 50000)
        // 注意：DP 解法的时间复杂度是 O(N^2)，如果长度直接冲到
        // 50000，跑一轮就需要 25 亿次计算，会极慢。
        // 为了能在合理时间内跑完大量随机测试，这里将大样本控制在少量轮次，或日常随机限制在
        // 2000 以内。 如果想纯测大样本，可调整此处。
        int size = getRandom(2, 2000);

        // 每 50 轮抽查一次极限超大样本
        if (t % 50 == 0) {
            size = getRandom(30000, 50000);
            printf("  [第 %d 轮] 触发大数据量压测，当前数组长度: %d ...\n", t,
                   size);
        }

        // 2. 动态分配并随机填充数组 (0 <= A[i] <= 50000)
        int* nums = (int*)malloc(sizeof(int) * size);
        for (int i = 0; i < size; i++) {
            nums[i] = getRandom(0, 50000);
        }

        // 3. 分别用两个算法计算结果
        int resStack = maxWidthRamp_Stack(nums, size);
        int resDP = maxWidthRamp_DP(nums, size);

        // 4. 比对结果
        if (resStack != resDP) {
            printf("\n❌ 测试失败！在第 %d 轮发现不一致：\n", t);
            printf("数组长度: %d\n", size);
            if (size <= 30) {  // 数组较小时才打印，否则刷屏
                printf("对应数组: ");
                printArray(nums, size);
            }
            printf("单调栈（正确答案）输出: %d\n", resStack);
            printf("动态规划解法输出: %d\n", resDP);

            free(nums);
            success = 0;
            break;
        }

        free(nums);

        if (t % 50 == 0) {
            printf("  [第 %d 轮] 压测通过！\n", t);
        }
    }

    if (success) {
        printf("\n恭喜！通过了 %d 轮大规模随机测试，双解法完全一致！\n",
               testTimes);
    }

    return 0;
}
