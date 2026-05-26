#include <stdlib.h>

#define MMAX(a, b) ((a) > (b) ? (a) : (b))
#define MMIN(a, b) ((a) > (b) ? (b) : (a))

int trap(int* height, int heightSize) {
    int n = heightSize;
    int* l_max = calloc(n, sizeof(int));
    int* r_max = calloc(n, sizeof(int));
    for (int i = 1; i < n - 1; ++i)
        l_max[i] = MMAX(l_max[i - 1], height[i - 1]);
    for (int i = n - 2; i > 0; --i)
        r_max[i] = MMAX(r_max[i + 1], height[i + 1]);

    int res = 0;
    // 按列累计
    for (int i = 1; i < n - 1; ++i) {
        // i 位置两侧最高的较小者
        int m = MMIN(l_max[i], r_max[i]);
        res += MMAX(m - height[i], 0);
    }

    return res;
}
