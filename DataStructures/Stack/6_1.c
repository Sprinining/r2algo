#define MMAX(a, b) ((a) > (b) ? (a) : (b))

int* arr;
int n;

int dfs(int l, int r) {
    if (l >= r) return 0;
    if (arr[l] <= arr[r]) return r - l;
    return MMAX(dfs(l + 1, r), dfs(l, r - 1));
}

int maxWidthRamp(int* nums, int numsSize) {
    arr = nums;
    n = numsSize;
    return dfs(0, n - 1);
}
