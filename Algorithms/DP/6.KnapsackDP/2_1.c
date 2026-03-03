#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long long mmax(long long a, long long b) { return a > b ? a : b; }

// 标准的 01 背包
long long bag(int n, int m, int** choice) {
    int rows = n + 1;
    int columns = m + 1;
    long long** dp = malloc(sizeof(*dp) * rows);
    long long* data = calloc(rows * columns, sizeof(*data));
    for (int i = 0; i < rows; ++i) dp[i] = data + i * columns;

    for (int i = 1; i < rows; ++i) {
        for (int j = 1; j < columns; ++j) {
            long long p1 = dp[i - 1][j];
            long long p2 = 0;
            if (j >= choice[i - 1][0]) p2 = dp[i - 1][j - choice[i - 1][0]] + choice[i - 1][1];
            dp[i][j] = mmax(p1, p2);
        }
    }
    return dp[n][m];
}

// 负权值的 01 背包
int main() {
    int n, x;
    scanf("%d %d", &n, &x);
    int** choice = malloc(sizeof(*choice) * n);
    int* data = malloc(sizeof(*data) * n * 2);

    long long res = 0;
    int idx = 0;
    int money = x;
    for (int i = 0, a, b, w, c; i < n; ++i) {
        scanf("%d %d %d", &a, &b, &w);
        c = 2 * b - a;
        if (c <= 0) {
            // 负权值，说明打折力度大，甚至能增加心里预算，一定选
            res += w;
            // 增加预算
            money -= c;
        } else {
            // 其余的当作普通的 01 背包
            choice[idx] = data + idx * 2;
            // 代价是 c 而不是 b
            choice[idx][0] = c;
            choice[idx][1] = w;
            ++idx;
        }
    }
    res += bag(idx, money, choice);
    printf("%lld", res);
}

/*
    每个游戏：原价：aᵢ、现价：bᵢ、快乐值：wᵢ
    允许超预算，但必须满足：总优惠 ≥ 超预算金额
    A = ∑ aᵢ   原价总和
    B = ∑ bᵢ   实际花的钱
    D = ∑ (aᵢ - bᵢ)   总优惠
    心理不亏条件：D ≥ B - X，将 D = A - B 代入移项 X ≥ 2B - A，即 ∑ (2bᵢ - aᵢ) ≤ X
    令 cᵢ = 2bᵢ - aᵢ，问题变成：选若干游戏，使得 ∑ cᵢ ≤ X，快乐值最大

    但有个坑：cᵢ 可能是负数。
    如果 2bᵢ - aᵢ < 0 说明这个游戏折扣特别大。买它不增加压力，甚至“扩大”心理容量。
    第一步：处理 cᵢ ≤ 0 的物品，这些必买
        总快乐 += wᵢ
        X -= cᵢ   （注意 cᵢ 是负数，相当于容量变大）
    第二步：对剩余 cᵢ > 0 的物品做普通 0/1 背包
        dp[j] = max(dp[j], dp[j - cᵢ] + wᵢ)
*/

/*
    为什么这种题型天然容易变成背包?
    因为背包本质上就是：
        选择若干个东西
        满足一个总限制
        让总收益最大
    原始条件是：优惠 ≥ 超预算
    翻译成：∑ f(i) ≥ ∑ g(i) - 常数
    关键在于把约束挪到一边。把所有东西移到左边，变成 ∑ 某种表达式 ≤ 常数

    例1：利润不亏本
        每个项目：收入 rᵢ，成本 cᵢ
        要求：总收入 ≥ 总成本
        移项：∑ (cᵢ - rᵢ) ≤ 0
    
    例2：平均值问题
        选一些数，使得：平均值 ≥ K
        等价于：∑ (aᵢ - K) ≥ 0

    例3：性价比最大
        ∑ value / ∑ cost 最大
        二分答案 + 转成：∑ (value - mid * cost) ≥ 0
    
    几乎都能：
        移项
        合并求和
        定义新权值
        变成 ∑ weight ≤ limit
*/