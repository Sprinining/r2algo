#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct parent {
    int v;
    int p;
    int child_idx;
    int child[2][2];
} parent;

int mmax(int a, int b) { return a > b ? a : b; }

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    // 花费都是 10 的整数倍，可以先除 10，dp 表的规模就能小 10 倍
    n /= 10;

    int (*all)[3] = malloc(sizeof(*all) * m);
    int parent_cnt = 0;
    for (int i = 0; i < m; ++i) {
        scanf("%d %d %d", &all[i][0], &all[i][1], &all[i][2]);
        all[i][0] /= 10;
        // 收益
        all[i][1] *= all[i][0];
        // -1 表示主件，否则表示主件在 all 的下标
        if (--all[i][2] == -1) ++parent_cnt;
    }

    // 主件组共 parent_cnt 个主件
    parent* parent_item = malloc(sizeof(*parent_item) * parent_cnt);
    // 记录主件在 all 中的下标与在主件组下标的映射
    int* map = malloc(sizeof(*map) * m);

    for (int i = 0, parent_idx = 0; i < m; ++i) {
        if (all[i][2] != -1) continue;
        // 主件
        parent_item[parent_idx].v = all[i][0];
        parent_item[parent_idx].p = all[i][1];
        parent_item[parent_idx].child_idx = 0;
        map[i] = parent_idx;
        ++parent_idx;
    }

    for (int i = 0; i < m; ++i) {
        if (all[i][2] == -1) continue;
        // 附件
        int p_idx = map[all[i][2]];
        int c_idx = parent_item[p_idx].child_idx;
        parent_item[p_idx].child[c_idx][0] = all[i][0];
        parent_item[p_idx].child[c_idx][1] = all[i][1];
        ++(parent_item[p_idx].child_idx);
    }

    int rows = parent_cnt + 1;
    int cols = n + 1;
    int** dp = malloc(sizeof(*dp) * rows);
    int* data = calloc(rows * cols, sizeof(*data));
    for (int i = 0; i < rows; ++i) dp[i] = data + i * cols;

    for (int i = 1; i < rows; ++i) {
        for (int j = 1; j < cols; ++j) {
            parent item = parent_item[i - 1];
            // 不要主件
            int p1 = dp[i - 1][j];
            // 只要主件
            int p2 = item.v <= j ? dp[i - 1][j - item.v] + item.p : 0;

            int p3 = 0, p4 = 0, p5 = 0;
            // 带上第一个附件
            if (item.child_idx >= 1) {
                int val = item.child[0][0] + item.v;
                p3 = val <= j ? dp[i - 1][j - val] + item.p + item.child[0][1] : 0;
            }
            if (item.child_idx == 2) {
                // 带上第二个附件
                int val = item.child[1][0] + item.v;
                p4 = val <= j ? dp[i - 1][j - val] + item.p + item.child[1][1] : 0;
                // 带上两个附件
                val += item.child[0][0];
                p5 = val <= j ? dp[i - 1][j - val] + item.p + item.child[0][1] + item.child[1][1]
                              : 0;
            }
            dp[i][j] = mmax(mmax(mmax(p1, p2), mmax(p3, p4)), p5);
        }
    }

    printf("%d", dp[rows - 1][cols - 1] * 10);
}

/*
    先把每个主件和它的附件分组，附件不能单独选，只能随主件。
    枚举每个组的所有合法组合（主件单独、主件+附件1、主件+附件2、主件+两个附件）。
    把每个组合当作一个物品加入 0/1 背包：价格 = 主件+附件总价，价值 = 主件+附件总价值。
    用背包 DP 求最大总价值，即可保证依赖关系和最优解。
*/