// transactions[i] = [from, to, amount] 表示 from 给 to 转了 amount 元
// 计算让所有人债务清零所需的【最小交易次数】

#include <stdio.h>
#include <string.h>

#define MAXN 13  // 人员 ID 最大为 12（0~12），题目限制人数 ≤12
#define MMAX(a, b) ((a) > (b) ? (a) : (b))

int debt[MAXN];     // 存储每个人的净负债/净资产：正数=应收，负数=应付
int n;              // 实际有债务的人数（过滤掉收支为0的人）
int dp[1 << MAXN];  // 状态压缩 DP 数组：dp[stat] = 状态 stat 下最多能分成多少个零和子集

// 填充好 debt 数组
void generateDebt(int** transactions, int tSize) {
    int nums[MAXN];
    memset(nums, 0, sizeof(nums));
    for (int i = 0; i < tSize; ++i) {
        int from = transactions[i][0];
        int to = transactions[i][1];
        int money = transactions[i][2];
        nums[from] -= money;
        nums[to] += money;
    }
    // 只保留有收支的人，过滤掉收支为 0 的人
    n = 0;
    for (int i = 0; i < MAXN; ++i) {
        if (nums[i] == 0) continue;
        debt[n++] = nums[i];
    }
}

// 返回当前状态下，最多能划分出多少个【累加和为0且不可拆分】的子集
// stat：二进制状态，每一位表示该人员是否还在当前集合中
// sum：当前集合的总金额和
// 核心思想：
// 1. 一个集合和为 0，最少需要元素个数 -1 次转账平账
// 2. 能划分的独立零和子集越多，总转账次数越少
// 3. 最小次数 = 总人数 - 最大非空零和子集数量
int dfs(int stat, int sum) {
    // 集合中只剩 0 或 1 个人，无法构成非空零和子集
    if ((stat & (stat - 1)) == 0) return 0;
    if (dp[stat] != -1) return dp[stat];

    int res = 0;  // 记录最大子集数量
    if (sum == 0) {
        // 找到任意一个还在集合里的人，把他去掉
        for (int i = 0; i < n; ++i) {
            if (((stat >> i) & 1)) {
                // 去掉 i，剩余集合继续递归 + 当前子集有效（+1）
                // +1 指的是当前取出的这个 i，和剩下的所有的划分完毕后剩余的几个
                // 凑一块和一定为0，因为一开始所有的总和就是 0
                res = dfs(stat ^ (1 << i), sum - debt[i]) + 1;
                break;  // 只需去掉任意一个，结果一样，直接跳出
            }
        }
    } else {
        // 尝试去掉每一个还在集合里的人，取最大值
        for (int i = 0; i < n; ++i) {
            // 不在集合里，跳过
            if (((stat >> i) & 1) == 0) continue;
            res = MMAX(res, dfs(stat ^ (1 << i), sum - debt[i]));
        }
    }

    dp[stat] = res;
    return res;
}

int minTransfers(int** transactions, int tSize) {
    generateDebt(transactions, tSize);
    memset(dp, -1, sizeof(dp));
    // 初始状态：所有人都在集合中（二进制全1），总和为 0
    int maxSubsets = dfs((1 << n) - 1, 0);
    // 最小转账次数 = 总人数 - 最大独立零和子集数
    return n - maxSubsets;
}

int main() {
    // 测试用例1：闭环交易，互相抵消，答案 0
    int case1[3][3] = {{0, 1, 10}, {1, 2, 10}, {2, 0, 10}};
    int* p1[] = {case1[0], case1[1], case1[2]};

    // 测试用例2：链式转账，无法抵消，答案 2
    int case2[2][3] = {{0, 1, 10}, {1, 2, 5}};
    int* p2[] = {case2[0], case2[1]};

    // 测试用例3：四人闭环，完全抵消，答案 0
    int case3[4][3] = {{0, 1, 5}, {1, 2, 5}, {2, 3, 5}, {3, 0, 5}};
    int* p3[] = {case3[0], case3[1], case3[2], case3[3]};

    // 测试用例4：一人借三人，必须转3次，答案 3
    int case4[3][3] = {{0, 1, 10}, {0, 2, 10}, {0, 3, 10}};
    int* p4[] = {case4[0], case4[1], case4[2]};

    // 测试用例5：复杂混合交易，答案 3
    int case5[5][3] = {{0, 1, 10}, {2, 0, 5}, {3, 4, 7}, {4, 2, 5}, {1, 3, 2}};
    int* p5[] = {case5[0], case5[1], case5[2], case5[3], case5[4]};

    // 整合所有测试用例
    int** testCases[] = {p1, p2, p3, p4, p5};
    int transactionSizes[] = {3, 2, 4, 3, 5};
    int expected[] = {0, 2, 0, 3, 3};

    // 执行测试并输出结果
    for (int i = 0; i < 5; i++) {
        int ans = minTransfers(testCases[i], transactionSizes[i]);
        printf("Test Case %d: Output = %d, Expected = %d %s\n\n", i + 1, ans, expected[i],
               (ans == expected[i]) ? "✅" : "❌");
    }

    return 0;
}
