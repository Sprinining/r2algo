#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define MMAX(a, b) ((a) > (b) ? (a) : (b))
#define MMIN(a, b) ((a) > (b) ? (b) : (a))

int dfs(int *nums, int l, int r) {
    if (l > r) return 0;
    if (l == r) return nums[l];
    // 选了 nums[l] 后，轮到对手选，对手选完只会留下更不利的情况给自己
    int p1 = nums[l] + MMIN(dfs(nums, l + 2, r), dfs(nums, l + 1, r - 1));
    int p2 = nums[r] + MMIN(dfs(nums, l, r - 2), dfs(nums, l + 1, r - 1));
    return MMAX(p1, p2);
}

bool predictTheWinner(int *nums, int numsSize) {
    int total = 0;
    for (int i = 0; i < numsSize; ++i) total += nums[i];
    int score = dfs(nums, 0, numsSize - 1);
    return (total - 2 * score) <= 0;
}
