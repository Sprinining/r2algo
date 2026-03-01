// 有效涂色问题
// 给定 n、m 两个参数
// 一共有 n 个格子，每个格子可以涂上一种颜色，颜色在 m 种里选
// 当涂满 n 个格子，并且m种颜色都使用了，叫一种有效方法
// 求一共有多少种有效的涂色方法
// 1 <= n, m <= 5000
// 结果比较大请 % 1000000007 之后返回
// 对数器验证

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>

int MOD = 1000000007;
int map[5001] = {0};
int res;

/*
    暴力递归“带路径”是因为状态依赖具体格子顺序和每种颜色的使用情况，
    状态信息太大，无法直接用二维 DP 表表示；
    必须改变状态定义（只记录用了多少种颜色）才能做可行的 DP
*/
// 暴力递归
// cur 表示当前格子下标
void recursive(int n, int m, int cur) {
    // 所有格子都涂完了
    if (cur == n) {
        // 检查是否每种颜色都用了
        for (int i = 0; i < m; i++)
            if (map[i] == 0) return;
        res = ((long long)res + 1) % MOD;
        return;
    }
    // 尚未涂完，则在当前位置尝试每种颜色
    for (int i = 0; i < m; i++) {
        // 使用 i 号颜色
        map[i]++;
        // 尝试下个位置
        recursive(n, m, cur + 1);
        // 回溯
        map[i]--;
    }
}

int paint1(int n, int m) {
    res = 0;
    recursive(n, m, 0);
    return res;
}

int paint2(int n, int m) {
    // dp[i][j] 表示前 i 个格子，总共用 j 种不同颜色的涂色方案数
    int rows = n + 1;
    int columns = m + 1;
    int** dp = malloc(sizeof(*dp) * rows);
    int* data = calloc(rows * columns, sizeof(*data));
    for (int i = 0; i < rows; i++) dp[i] = data + i * columns;

    // 0 行和 0 列不考虑
    // 1 行，用不完 j 种，全都是 0
    // 1 列，并不是 1
    for (int i = 1; i < rows; i++) dp[i][1] = m;

    for (int i = 2; i < rows; i++) {
        for (int j = 2; j < columns; j++) {
            // 新增一个格子，用的是已有的颜色
            long long p1 = ((long long)dp[i - 1][j] * j) % MOD;
            // 新增一个格子，用的是新的颜色
            long long p2 = ((long long)dp[i - 1][j - 1] * (m - j + 1)) % MOD;
            // 为何与 dp[i][j-1] 无关？
            // 不能在同一行的状态 dp[i][j-1] 上直接做操作得到 j 种颜色，因为当前格子已经算过了，它无法再“增加颜色数”
            // 状态转移只能通过前一格子 i-1 的状态来引入新颜色
            dp[i][j] = (p1 + p2) % MOD;
        }
    }
    return dp[n][m];
}

// 验证器
void test() {
    int N = 5;  // 暴力测试最大 n
    int M = 5;  // 暴力测试最大 m
    printf("功能验证开始\n");
    for (int n = 1; n <= N; n++) {
        for (int m = 1; m <= M; m++) {
            int ans1 = paint1(n, m);
            int ans2 = paint2(n, m);
            if (ans1 != ans2) {
                printf("出错！n=%d, m=%d, paint1=%d, paint2=%d\n", n, m, ans1, ans2);
            } else {
                printf("n=%d, m=%d, 验证通过, ans=%d\n", n, m, ans1);
            }
        }
    }
    printf("功能验证结束\n");
}

int main() {
    SetConsoleOutputCP(CP_UTF8);  // 设置控制台输出为 UTF-8
    test();

    // 性能测试
    int n = 5000, m = 5000;
    printf("性能测试 n=%d, m=%d\n", n, m);
    long long start = clock();
    int ans = paint2(n, m);
    long long end = clock();
    printf("结果: %d, 运行时间: %lld ms\n", ans, (end - start));
    return 0;
}