#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MMAX(a, b) ((a) > (b) ? (a) : (b))
#define MMIN(a, b) ((a) > (b) ? (b) : (a))

int **dp;
int *data;

bool predictTheWinner(int *nums, int numsSize) {
    int total = 0;
    for (int i = 0; i < numsSize; ++i) total += nums[i];
    dp = malloc(sizeof(*dp) * numsSize);
    data = calloc(numsSize * numsSize, sizeof(*data));
    for (int i = 0; i < numsSize; ++i) dp[i] = data + i * numsSize;

    // 初始化起始点
    for (int i = 0; i < numsSize; ++i) dp[i][i] = nums[i];
    for (int i = 0; i + 1 < numsSize; ++i) dp[i][i + 1] = MMAX(nums[i], nums[i + 1]);

    // 从下往上，从左往右填写
    for (int i = numsSize - 3; i >= 0; --i) {
        for (int j = i + 2; j < numsSize; ++j) {
            int p1 = nums[i] + MMIN(dp[i + 2][j], dp[i + 1][j - 1]);
            int p2 = nums[j] + MMIN(dp[i][j - 2], dp[i + 1][j - 1]);
            dp[i][j] = MMAX(p1, p2);
        }
    }
    return (total - 2 * dp[0][numsSize - 1]) <= 0;
}
