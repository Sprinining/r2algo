#include <string.h>

// 暴力递归
int numDistinct(char* s, char* t) {
    int len_s = strlen(s);
    int len_t = strlen(t);
    int res = 0;

    // 子序列共有 2^(len_s) 个
    // 实际上 1 <= s.length, t.length <= 1000，mask 无法保存完整信息
    for (int mask = 0; mask < (1 << len_s); mask++) {
        char sub[1001];
        int idx = 0;
        // 根据位掩码生成子序列
        for (int i = 0; i < len_s; i++)
            if ((mask & (1 << i)) != 0) sub[idx++] = s[i];
        sub[idx] = '\0';
        if (strcmp(sub, t) == 0) res++;
    }
    return res;
}