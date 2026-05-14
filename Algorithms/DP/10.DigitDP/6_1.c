#include <stdio.h>
#include <string.h>

#define MOD 1000000007
#define MAXN 1005

typedef long long ll;

// dp[i][pp][p][free]
// i: 当前处理到第几位
// pp: 前前一位数字，10 表示不存在
// p: 前一位数字，10 表示不存在
// free: 是否已经自由选择
int dp[MAXN][11][11][2];

// 判断一个数是否为萌数
// 萌数：存在长度 >= 2 的回文子串
// 实际只需要检查 aa 和 aba
int check(char* num) {
    int len = strlen(num);
    for (int i = 0; i < len; ++i) {
        if (i >= 1 && num[i] == num[i - 1]) return 1;
        if (i >= 2 && num[i] == num[i - 2]) return 1;
    }
    return 0;
}

// 返回从 i 开始构造的“非萌数”方案数
int fc(char* num, int i, int pp, int p, int freeFlag) {
    if (i == strlen(num)) return 1;
    if (dp[i][pp][p][freeFlag] != -1) return dp[i][pp][p][freeFlag];

    int res = 0;
    // 当前位上限
    int up = freeFlag ? 9 : num[i] - '0';

    // 枚举当前位填写的数字
    for (int cur = 0; cur <= up; ++cur) {
        // 处理前导 0，表示前面还没开始填数字
        if (p == 10 && cur == 0) {
            res = fc(num, i + 1, 10, 10, 1);
            continue;
        }
        // 出现 aa 或 aba，说明形成回文
        if (cur == p || cur == pp) continue;
        // 判断下一位是否自由
        int nextFree = (freeFlag || cur < up);
        res = ((ll)res + fc(num, i + 1, p, cur, nextFree)) % MOD;
    }

    return dp[i][pp][p][freeFlag] = (int)res;
}

// 计算 [0, num] 中非萌数数量
int countNonM(char* num) {
    memset(dp, -1, sizeof(dp));
    return fc(num, 0, 10, 10, 0);
}

// 计算 [0, num] 中萌数数量
int cnt(char* num) {
    if (num[0] == '0') return 0;

    // 计算 num 的值
    ll all = 0;
    ll base = 1;
    int len = strlen(num);

    for (int i = len - 1; i >= 0; --i) {
        all = (all + base * (num[i] - '0')) % MOD;
        base = (base * 10) % MOD;
    }

    // 非萌数数量
    int notM = countNonM(num);

    // 萌数 = 总数 - 非萌数
    return (int)((all - notM + MOD) % MOD);
}

// 计算区间 [l, r] 中萌数数量
int compute(char* l, char* r) {
    int res = (cnt(r) - cnt(l) + MOD) % MOD;
    // cnt(l) 没包含 l 自己，如果 l 是萌数需要补回来
    if (check(l)) res = ((ll)res + 1) % MOD;
    return res;
}

int main() {
    char l[MAXN];
    char r[MAXN];
    scanf("%s %s", l, r);
    printf("%d\n", compute(l, r));

    return 0;
}
