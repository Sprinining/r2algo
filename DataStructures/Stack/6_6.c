#define MAXN 50005
#define MMAX(a, b) ((a) > (b) ? (a) : (b))

int stk[MAXN];
int sz;
int* arr;

// 在递减数组 stk 中 [left, right] 上找第一个小于等于 target 的位置
int binary_search(int left, int right, int target) {
    int l = left, r = right;
    int m;
    while (l <= r) {
        m = l + ((r - l) >> 1);
        if (arr[stk[m]] <= target) {
            r = m - 1;
        } else {
            l = m + 1;
        }
    }
    return l;
}

int maxWidthRamp(int* nums, int numsSize) {
    arr = nums;
    int n = numsSize;
    sz = 0;

    // 递减栈，栈中放着可能的起始位置
    for (int i = 0; i < n; ++i) {
        // 如果当前值比栈顶还大或者等于
        // 那就没必要入栈，以为栈中更小元素开头可以获得更大宽度
        if (sz == 0 || nums[stk[sz - 1]] > nums[i]) {
            stk[sz++] = i;
        }
    }

    int res = 0;
    // 以 i 位置为结尾，找最大宽度
    for (int i = n - 1; i >= 0; --i) {
        if (sz == 0) break;
        int idx = binary_search(0, sz - 1, nums[i]);
        // 没找到
        if (idx == sz) continue;
        res = MMAX(res, i - stk[idx]);
        sz = idx;
    }
    return res;
}
