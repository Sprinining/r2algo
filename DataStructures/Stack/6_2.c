#include <stdlib.h>
#include <string.h>

#define MMAX(a, b) ((a) > (b) ? (a) : (b))

int* arr;
int n;
int** dp;
int* data;

int dfs(int l, int r) {
    if (l >= r) return 0;
    if (dp[l][r] != -1) return dp[l][r];
    if (arr[l] <= arr[r]) return dp[l][r] = r - l;
    return dp[l][r] = MMAX(dfs(l + 1, r), dfs(l, r - 1));
}

int maxWidthRamp(int* nums, int numsSize) {
    arr = nums;
    n = numsSize;

    data = malloc(sizeof(int) * n * n);
    memset(data, -1, sizeof(int) * n * n);
    dp = malloc(sizeof(int*) * n);
    for (int i = 0; i < n; ++i) dp[i] = data + i * n;

    return dfs(0, n - 1);
}
