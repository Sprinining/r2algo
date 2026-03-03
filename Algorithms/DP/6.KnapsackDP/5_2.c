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
    n /= 10;

    int (*all)[3] = malloc(sizeof(*all) * m);
    int parent_cnt = 0;
    for (int i = 0; i < m; ++i) {
        scanf("%d %d %d", &all[i][0], &all[i][1], &all[i][2]);
        all[i][0] /= 10;
        all[i][1] *= all[i][0];
        if (--all[i][2] == -1) ++parent_cnt;
    }

    parent* parent_item = malloc(sizeof(*parent_item) * parent_cnt);
    int* map = malloc(sizeof(*map) * m);

    for (int i = 0, parent_idx = 0; i < m; ++i) {
        if (all[i][2] != -1) continue;
        parent_item[parent_idx].v = all[i][0];
        parent_item[parent_idx].p = all[i][1];
        parent_item[parent_idx].child_idx = 0;
        map[i] = parent_idx;
        ++parent_idx;
    }

    for (int i = 0; i < m; ++i) {
        if (all[i][2] == -1) continue;
        int p_idx = map[all[i][2]];
        int c_idx = parent_item[p_idx].child_idx;
        parent_item[p_idx].child[c_idx][0] = all[i][0];
        parent_item[p_idx].child[c_idx][1] = all[i][1];
        ++(parent_item[p_idx].child_idx);
    }

    int rows = parent_cnt + 1;
    int cols = n + 1;
    int* dp = calloc(cols, sizeof(*dp));

    // 空间压缩
    for (int i = 1; i < rows; ++i) {
        for (int j = cols - 1; j > 0; --j) {
            parent item = parent_item[i - 1];
            int p1 = dp[j];
            int p2 = item.v <= j ? dp[j - item.v] + item.p : 0;

            int p3 = 0, p4 = 0, p5 = 0;
            if (item.child_idx >= 1) {
                int val = item.child[0][0] + item.v;
                p3 = val <= j ? dp[j - val] + item.p + item.child[0][1] : 0;
            }
            if (item.child_idx == 2) {
                int val = item.child[1][0] + item.v;
                p4 = val <= j ? dp[j - val] + item.p + item.child[1][1] : 0;
                val += item.child[0][0];
                p5 = val <= j ? dp[j - val] + item.p + item.child[0][1] + item.child[1][1] : 0;
            }
            dp[j] = mmax(mmax(mmax(p1, p2), mmax(p3, p4)), p5);
        }
    }

    printf("%d", dp[cols - 1] * 10);
}