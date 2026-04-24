#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MMAX(a, b) ((a) > (b) ? (a) : (b))
#define MMIN(a, b) ((a) > (b) ? (b) : (a))

int **dp;
int *data;

int dfs(int *nums, int l, int r) {
    if (l > r) return 0;
    if (l == r) return nums[l];
    if (dp[l][r] != -1) return dp[l][r];
    int p1 = nums[l] + MMIN(dfs(nums, l + 2, r), dfs(nums, l + 1, r - 1));
    int p2 = nums[r] + MMIN(dfs(nums, l, r - 2), dfs(nums, l + 1, r - 1));
    dp[l][r] = MMAX(p1, p2);
    return dp[l][r];
}

bool predictTheWinner(int *nums, int numsSize) {
    int total = 0;
    for (int i = 0; i < numsSize; ++i) total += nums[i];
    dp = malloc(sizeof(*dp) * numsSize);
    data = malloc(sizeof(*data) * numsSize * numsSize);
    memset(data, -1, sizeof(*data) * numsSize * numsSize);
    for (int i = 0; i < numsSize; ++i) dp[i] = data + i * numsSize;

    int score = dfs(nums, 0, numsSize - 1);
    return (total - 2 * score) <= 0;
}
