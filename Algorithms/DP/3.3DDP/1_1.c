#include <stdlib.h>
#include <string.h>

#define MMAX(a, b) ((a) > (b) ? (a) : (b))

// 记录每个字符串 0 和 1 的个数
int (*cnts)[2];

// len 是状态的一部分（显式记录答案），答案在参数里，一路带着结果走
int dfs(int strsSize, int m, int n, int index, int len) {
    if (index == strsSize) return len;
    // 不选
    int p1 = dfs(strsSize, m, n, index + 1, len);
    // 选
    int z = cnts[index][0];
    int o = cnts[index][1];
    int p2 = (z <= m && o <= n) ? dfs(strsSize, m - z, n - o, index + 1, len + 1) : 0;
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

    return dfs(strsSize, m, n, 0, 0);
}