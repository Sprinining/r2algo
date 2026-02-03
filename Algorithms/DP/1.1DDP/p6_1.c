#include <stdbool.h>

bool isUgly(int n) {
    if (n <= 0) return false;
    while (n % 2 == 0) n /= 2;
    while (n % 3 == 0) n /= 3;
    while (n % 5 == 0) n /= 5;
    return n == 1;
}

int nthUglyNumber(int n) {
    int i = 1, k = 0;
    while (k < n) {
        if (isUgly(i)) k++;
        i++;
    }
    return i - 1;
}