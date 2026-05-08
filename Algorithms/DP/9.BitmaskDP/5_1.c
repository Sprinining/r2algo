#include <stdio.h>
#include <string.h>

#define MOD 1000000007
#define MAXN 10
typedef long long ll;

int n;
int** hats;
int* hatsColSize;
int dp[1ll << 41][MAXN];

// stat 从最低位到高位对应 1～40 号帽子是否还在，1 表示可选，最低位弃用
// cur 表示当前轮到 cur 号人挑选帽子
int dfs(ll stat, int cur) {
    if (cur == n) return 1;
    if (dp[stat][cur] != -1) return dp[stat][cur];
    int res = 0;
    for (int i = 0; i < hatsColSize[cur]; ++i) {
        int hat = hats[cur][i];
        if (((stat >> hat) & 1) == 0) continue;
        res = ((ll)res + dfs(stat ^ (1ll << hat), cur + 1)) % MOD;
    }
    dp[stat][cur] = res;
    return res;
}

// 理论正确但复杂度爆炸
int numberWays(int** _hats, int hatsSize, int* _hatsColSize) {
    hats = _hats;
    hatsColSize = _hatsColSize;
    n = hatsSize;
    memset(dp, -1, sizeof(dp));
    return dfs((1ll << 41) - 2, 0);
}

int main() {
    // 测试用例 1
    int p1[2] = {3, 4};
    int p2[2] = {4, 5};
    int p3[1] = {5};
    int* hats1[] = {p1, p2, p3};
    int col1[] = {2, 2, 1};
    printf("测试用例1: %d\n", numberWays(hats1, 3, col1));

    // 测试用例 2
    int a1[3] = {3, 5, 1};
    int a2[2] = {3, 5};
    int* hats2[] = {a1, a2};
    int col2[] = {3, 2};
    printf("测试用例2: %d\n", numberWays(hats2, 2, col2));

    // 测试用例 3
    int b1[4] = {1, 2, 3, 4};
    int b2[4] = {1, 2, 3, 4};
    int b3[4] = {1, 2, 3, 4};
    int b4[4] = {1, 2, 3, 4};
    int* hats3[] = {b1, b2, b3, b4};
    int col3[] = {4, 4, 4, 4};
    printf("测试用例3: %d\n", numberWays(hats3, 4, col3));

    return 0;
}
