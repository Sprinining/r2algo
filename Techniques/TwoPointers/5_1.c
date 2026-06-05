#define MMAX(a, b) ((a) > (b) ? (a) : (b))

int maxArea(int* height, int heightSize) {
    int res = 0;
    for (int l = 0, r = heightSize - 1; l <= r;) {
        if (height[l] < height[r]) {
            res = MMAX(res, (r - l) * height[l]);
            ++l;
        } else {
            res = MMAX(res, (r - l) * height[r]);
            --r;
        }
    }

    return res;
}
