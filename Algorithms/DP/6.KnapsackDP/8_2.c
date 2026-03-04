#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 最大物品数
#define MAXN 1000
// 最大的原始组编号
#define MAXCNT 10000

typedef struct {
    int item_cnt;
    int item[MAXN][2];
} group;

int mmax(int a, int b) { return a > b ? a : b; }

int main() {
    int m, n;
    scanf("%d %d", &m, &n);

    // 原始组号到新组号的映射
    int map[MAXCNT + 1];
    memset(map, -1, sizeof(map));

    group gp[MAXN];
    int gp_cnt = 0;

    for (int i = 0, a, b, c; i < n; ++i) {
        scanf("%d%d%d", &a, &b, &c);
        // 组号离散化
        if (map[c] == -1) {
            // 原始组号第一次出现，映射到新的组号
            gp[gp_cnt].item_cnt = 1;
            gp[gp_cnt].item[0][0] = a;
            gp[gp_cnt].item[0][1] = b;
            map[c] = gp_cnt++;
        } else {
            // 加到已有的组中
            int gp_idx = map[c];
            int item_idx = gp[gp_idx].item_cnt;
            gp[gp_idx].item[item_idx][0] = a;
            gp[gp_idx].item[item_idx][1] = b;
            ++(gp[gp_idx].item_cnt);
        }
    }

    int rows = gp_cnt + 1;
    int cols = m + 1;
    int* dp = calloc(cols, sizeof(*dp));

    for (int i = 1; i < rows; ++i) {
        for (int j = cols - 1; j > 0; --j) {
            // 该组一个不选
            int p = dp[j];
            // 要选也只能选一个
            for (int k = 0; k < gp[i - 1].item_cnt; ++k) {
                int cost = gp[i - 1].item[k][0];
                int val = gp[i - 1].item[k][1];
                if (cost <= j) p = mmax(p, dp[j - cost] + val);
            }
            dp[j] = p;
        }
    }

    printf("%d", dp[cols - 1]);
}