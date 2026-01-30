#include <stdio.h>

// 空间压缩
int fib(int n) {
    if (n < 2) return n;

    int p = 0;
    int q = 1;

    int k = 2;
    while (k <= n) {
        if (k % 2 == 0) {
            p += q;
        } else {
            q += p;
        }

        k++;
    }
    return (n % 2 == 0) ? p : q;
}