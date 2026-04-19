#include <stdlib.h>
#include <string.h>

#define MMAX(a, b) ((a) > (b) ? (a) : (b))

// 记录每个字符串 0 和 1 的个数
int (*cnts)[2];

// len 被隐藏在递归返回值里（隐式累加），每个状态返回自己的最优解
int dfs(int strsSize, int m, int n, int index) {
    if (index == strsSize) return 0;
    // 不选
    int p1 = dfs(strsSize, m, n, index + 1);
    // 选
    int z = cnts[index][0];
    int o = cnts[index][1];
    int p2 = (z <= m && o <= n) ? 1 + dfs(strsSize, m - z, n - o, index + 1) : 0;
    return MMAX(p1, p2);
}

int findMaxForm(char** strs, int strsSize, int m, int n) {
    cnts = malloc(sizeof(*cnts) * strsSize);
    for (int i = 0; i < strsSize; ++i) {
        int z = 0, slen = strlen(strs[i]);
        for (int j = 0; j < slen; ++j) {
            if (strs[i][j] == '0') ++z;
        }
        cnts[i][0] = z;
        cnts[i][1] = slen - z;
    }

    return dfs(strsSize, m, n, 0);
}