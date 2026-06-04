#define MMAX(a, b) ((a) > (b) ? (a) : (b))

int trap(int* height, int heightSize) {
    int n = heightSize;
    int max_height = 0;
    for (int i = 0; i < n; ++i) max_height = MMAX(max_height, height[i]);

    int water = 0;
    // 一层一层向上计算水槽面积
    for (int level = 1; level <= max_height; ++level) {
        int l = 0;
        // 寻找当前层的左边界
        // 从左往右找，直到找到第一个高度大于或等于当前 level 的柱子
        while (l < n && height[l] < level) ++l;
        // 如果整行都找不出一根柱子能达到这个高度，说明上面已经没有凹槽了，直接退出外层循环
        if (l >= n) break;
        // 用于累积当前左右边界之间的潜在的水位
        int temp = 0;

        // 从左边界的下一个位置开始，向右扫描寻找右边界
        for (int r = l + 1; r < n; ++r) {
            if (height[r] < level) {
                // 如果当前柱子高度低于 level，说明这里有一个空槽
                ++temp;
            } else if (height[r] >= level) {
                // 如果遇到了一个高度大于或等于 level，说明找到了一个右边界
                // 将临时积攒的水真正加到总水池中
                water += temp;
                temp = 0;
                // 当前的右边界变成新的左边界，继续向右试探
                l = r;
            }
        }
    }

    return water;
}
