#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 最大物品数
#define MAXN 1000
// 最大的原始组编号
#define MAXCNT 10001

int mmax(int a, int b) { return a > b ? a : b; }

typedef struct {
    int cost;
    int weight;
} Item;

typedef struct {
    int item_cnt;
    Item items[MAXN];
} Group;

Group gp[MAXN];
int gp_cnt;

// 原始组号到新组号的映射
int map[MAXCNT];

int main() {
    int m, n;
    scanf("%d%d", &m, &n);

    memset(map, -1, sizeof(map));
    gp_cnt = 0;

    for (int i = 0, a, b, c; i < n; ++i) {
        scanf("%d%d%d", &a, &b, &c);
        // 组号离散化
        if (map[c] == -1) {
            map[c] = gp_cnt++;
            gp[map[c]].item_cnt = 0;
        }
        // 新组号
        int gp_idx = map[c];
        gp[gp_idx].items[gp[gp_idx].item_cnt].cost = a;
        gp[gp_idx].items[gp[gp_idx].item_cnt].weight = b;
        ++(gp[gp_idx].item_cnt);
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
                int cost = gp[i - 1].items[k].cost;
                int val = gp[i - 1].items[k].weight;
                if (cost <= j) p = mmax(p, dp[j - cost] + val);
            }
            dp[j] = p;
        }
    }

    printf("%d", dp[cols - 1]);
}