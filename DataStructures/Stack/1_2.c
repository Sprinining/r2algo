#include <stdio.h>

#define MAXN 1000000

int arr[MAXN];
int stk[MAXN];  // 递增栈，存下标
int sz;
int right_smaller[MAXN];
int left_smaller[MAXN];

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) scanf("%d", &arr[i]);

    sz = 0;
    // 单次遍历，同时寻找左右两侧的更小值
    for (int i = 0; i < n; ++i) {
        // 当遇到比栈顶小的元素时，触发弹出
        while (sz > 0 && arr[stk[sz - 1]] > arr[i]) {
            int top = stk[--sz];
            // 右侧更小值：就是当前让它弹出的这个元素 i
            right_smaller[top] = i;
            // 左侧更小值：因为栈是单调递增的
            // 压在 top 底下的那个元素
            // 就是 top 左侧第一个比它小的元素
            left_smaller[top] = sz > 0 ? stk[sz - 1] : -1;
        }
        stk[sz++] = i;
    }

    // 清空栈中残留的元素
    while (sz > 0) {
        int top = stk[--sz];
        right_smaller[top] = -1;
        left_smaller[top] = sz > 0 ? stk[sz - 1] : -1;
    }

    // 修正相同元素带来的“左侧边界”误差
    // 如果原数组存在重复元素（例如 [2, 2, 2]），单调栈在处理时，
    // 后面的 2 会把前面的 2 误认为是它的“左侧更小值”
    for (int i = 1; i < n; ++i) {
        while (left_smaller[i] != -1 && arr[left_smaller[i]] == arr[i]) {
            left_smaller[i] = left_smaller[left_smaller[i]];
        }
    }

    for (int i = 0; i < n; ++i)
        printf("%d %d\n", left_smaller[i], right_smaller[i]);

    return 0;
}
