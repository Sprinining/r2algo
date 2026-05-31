#include <stdio.h>

#define MAXN 1000000

int arr[MAXN];
// 递增栈，栈里存下标
int stk[MAXN];
int top;
int right_smaller[MAXN];
int left_smaller[MAXN];

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) scanf("%d", &arr[i]);

    top = 0;
    for (int i = 0; i < n; ++i) {
        while (top > 0 && arr[stk[top - 1]] > arr[i]) {
            right_smaller[stk[--top]] = i;
        }
        stk[top++] = i;
    }
    while (top > 0) right_smaller[stk[--top]] = -1;

    for (int i = n - 1; i >= 0; --i) {
        while (top > 0 && arr[stk[top - 1]] > arr[i]) {
            left_smaller[stk[--top]] = i;
        }
        stk[top++] = i;
    }
    while (top > 0) left_smaller[stk[--top]] = -1;

    for (int i = 0; i < n; ++i)
        printf("%d %d\n", left_smaller[i], right_smaller[i]);

    return 0;
}
