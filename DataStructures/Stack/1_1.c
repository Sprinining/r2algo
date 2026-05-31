#include <stdio.h>

#define MAXN 1000000

int arr[MAXN];
int stk[MAXN];  // 单调递增栈，内部存储的是数组元素的“下标”
int sz;
int right_smaller[MAXN];  // 存储每个元素右边第一个比它小的元素的下标
int left_smaller[MAXN];   // 存储每个元素左边第一个比它小的元素的下标

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) scanf("%d", &arr[i]);

    // 从左向右遍历，寻找右边第一个比自己小的元素
    sz = 0;
    for (int i = 0; i < n; ++i) {
        // 如果栈不为空，且当前元素 arr[i] 比栈顶下标对应的元素还要小
        // 说明当前元素 i 就是栈顶元素右边遇到的“第一个更小值”
        while (sz > 0 && arr[stk[sz - 1]] > arr[i]) {
            right_smaller[stk[--sz]] = i;
        }
        // 将当前元素的下标入栈，继续保持栈内元素对应的值是单调递增的
        stk[sz++] = i;
    }
    // 遍历结束后，栈中残留的元素说明它们右边没有比它们更小的数了
    // 统一赋值为 -1
    while (sz > 0) right_smaller[stk[--sz]] = -1;

    for (int i = n - 1; i >= 0; --i) {
        while (sz > 0 && arr[stk[sz - 1]] > arr[i]) {
            left_smaller[stk[--sz]] = i;
        }
        stk[sz++] = i;
    }
    while (sz > 0) left_smaller[stk[--sz]] = -1;  // 统一赋值为 -1

    for (int i = 0; i < n; ++i)
        printf("%d %d\n", left_smaller[i], right_smaller[i]);

    return 0;
}
