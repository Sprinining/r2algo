#define MAXN 50005
#define MMAX(a, b) ((a) > (b) ? (a) : (b))

int stk[MAXN];
int sz;

int maxWidthRamp(int* nums, int numsSize) {
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
    for (int i = n - 1; i >= 0; --i) {
        while (sz > 0 && nums[stk[sz - 1]] <= nums[i]) {
            res = MMAX(res, i - stk[sz - 1]);
            --sz;
        }
    }
    return res;
}
