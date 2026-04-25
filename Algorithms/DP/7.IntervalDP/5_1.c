#include <stdio.h>
#include <stdlib.h>

#define MMAX(a, b) ((a) > (b) ? (a) : (b))

// 如果考虑最先打爆的气球，两侧没爆的气球不容易得到
// 如果考虑最后打爆的气球，两侧没爆的气球容易得到
// 函数调用前提：两侧一定有没爆的气球
// 返回在 [l, r] 上最大收益
int dfs(int* a, int l, int r) {
    if (l == r) return a[l - 1] * a[l] * a[l + 1];
    int res = 0;
    // [l, r] 上最后打爆 m
    for (int m = l; m <= r; ++m) {
        res = MMAX(res, a[l - 1] * a[m] * a[r + 1] + dfs(a, l, m - 1) + dfs(a, m + 1, r));
    }
    return res;
}

int maxCoins(int* nums, int numsSize) {
    // 两端各增加一个
    int len = numsSize + 2;
    int* arr = malloc(sizeof(*arr) * len);
    arr[0] = 1;
    arr[len - 1] = 1;
    for (int i = 0; i < numsSize; ++i) arr[i + 1] = nums[i];
    return dfs(arr, 1, len - 2);
}
