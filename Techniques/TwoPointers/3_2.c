#define MMAX(a, b) ((a) > (b) ? (a) : (b))

int trap(int* height, int heightSize) {
    int n = heightSize;
    int l_max = height[0];
    int r_max = height[n - 1];
    int l = 1, r = n - 2;
    int res = 0;

    while (l <= r) {
        if (l_max < r_max) {
            // l 左侧最大值就是 l_max，左侧都是遍历过的
            // l 右侧最大值一定大于等于 r_max，因为 [l, r] 这一段还有些没遍历到
            // 如果此时 l_max < r_max，那么 l 位置就可以结算了
            res += MMAX(l_max - height[l], 0);
            // 更新 l_max
            l_max = MMAX(l_max, height[l]);
            ++l;
        } else {
            res += MMAX(r_max - height[r], 0);
            r_max = MMAX(r_max, height[r]);
            --r;
        }
    }

    return res;
}
