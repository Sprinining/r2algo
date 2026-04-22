#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define IDX(i, j, k) ((i) * (J) * (K) + (j) * (K) + (k))

int cnt[26];
int I, J, K;
// dp[k][r][c] = s1 从 r 下标开始和 s2 从 c 下标开始长度为 k 的字符串是否是扰乱字符串
bool* dp;

bool isScramble(char* s1, char* s2) {
    I = strlen(s1) + 1;
    J = strlen(s1);
    K = strlen(s1);
    dp = malloc(sizeof(*dp) * I * J * K);
    memset(dp, 0, sizeof(*dp) * I * J * K);

    for (int r = 0; r < J; ++r)
        for (int c = 0; c < K; ++c) dp[IDX(1, r, c)] = s1[r] == s2[c];

    for (int k = 2; k < I; ++k) {
        // 注意循环范围
        for (int r = 0; r + k <= J; ++r) {
            for (int c = 0; c + k <= K; ++c) {
                bool res = false;
                for (int i = 1; i < k; ++i) {
                    if (dp[IDX(i, r, c)] && dp[IDX(k - i, r + i, c + i)]) {
                        res = true;
                        break;
                    }
                }
                if (!res) {
                    for (int i = 1; i < k; ++i) {
                        if (dp[IDX(i, r, c + k - i)] && dp[IDX(k - i, r + i, c)]) {
                            res = true;
                            break;
                        }
                    }
                }
                dp[IDX(k, r, c)] = res;
            }
        }
    }
    return dp[IDX(strlen(s1), 0, 0)];
}
