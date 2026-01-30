#include <stdio.h>

// https://leetcode.cn/problems/fibonacci-number/

// 暴力递归
int fib(int n) {
    if (n < 2) return n;
    return fib(n - 1) + fib(n - 2);
}