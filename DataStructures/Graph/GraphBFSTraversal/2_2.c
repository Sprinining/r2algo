#include <stdlib.h>
#include <string.h>

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define INF 0x3f3f3f3f

int minStickers(char** stickers, int stickersSize, char* target) {
    int m = strlen(target);
    int max_state = 1 << m;

    // dp[state] 表示达到 state 状态（即消去 state
    // 对应的二进制位上的字符）所需的最少贴纸数
    int* dp = (int*)malloc(sizeof(int) * max_state);
    // 初始化所有状态为无穷大
    memset(dp, 0x3f, sizeof(int) * max_state);

    // 初始状态：什么都还没消去，需要 0 张贴纸
    dp[0] = 0;

    // 遍历每一个状态（从 0 开始往上递推）
    for (int state = 0; state < max_state; state++) {
        // 如果当前状态不可达，直接跳过
        if (dp[state] == INF) continue;

        // 尝试用每一张贴纸去更新能到达的新状态
        for (int i = 0; i < stickersSize; i++) {
            int next_state = state;
            char* sticker = stickers[i];
            int len = strlen(sticker);

            // 统计这枚贴纸中的各个字符数量（可以用动态计数的方案）
            // 为了高效，我们在循环里直接去匹配当前 state 下还缺少的字符
            int sticker_cnt[26] = {0};
            for (int k = 0; k < len; k++) {
                sticker_cnt[sticker[k] - 'a']++;
            }

            // 复制一份贴纸的字符统计，用于模拟消除
            int remain_cnt[26];
            memcpy(remain_cnt, sticker_cnt, sizeof(sticker_cnt));

            // 遍历 target 的每一位，看当前贴纸能不能消去它
            for (int j = 0; j < m; j++) {
                // 如果 target 的第 j 位在当前 state 中已经是
                // 1（代表已被消去），我们不需要再消它
                if ((next_state >> j) & 1) continue;

                // 如果没被消去，且贴纸里有这个字符
                int ch_idx = target[j] - 'a';
                if (remain_cnt[ch_idx] > 0) {
                    // 消去该字符，贴纸库存减 1
                    remain_cnt[ch_idx]--;
                    // 将 next_state 的第 j 位置为 1
                    next_state |= (1 << j);
                }
            }

            // 如果这张贴纸确实能让状态发生改变（消去了新字符）
            if (next_state != state) {
                dp[next_state] = MIN(dp[next_state], dp[state] + 1);
            }
        }
    }

    // 最终目标是把 target 的每一位都消掉，即二进制全为 1 的状态
    int ans = dp[max_state - 1];
    free(dp);

    return (ans == INF) ? -1 : ans;
}
