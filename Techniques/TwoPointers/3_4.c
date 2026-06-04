#define MMIN(a, b) ((a) > (b) ? (b) : (a))
#define MAXN 20005

int stk[MAXN];
int sz;

int trap(int* height, int heightSize) {
    sz = 0;
    int water = 0;

    // 遍历每一个柱子，当前柱子的下标为 r (代表右边界 Right)
    for (int r = 0; r < heightSize; ++r) {
        int cur = height[r];

        // 如果栈不为空，且当前高度大于栈顶柱子的高度
        // 说明遇到了一个“上升沿”，与栈内的更矮柱子形成了凹槽，可以开始横向计算水坑面积了
        while (sz > 0 && height[stk[sz - 1]] < cur) {
            // 弹出栈顶元素，将其作为凹槽的底部
            int top = stk[--sz];
            // 如果弹出了底部之后栈空了，说明左边没有更高的柱子挡着，水会漏掉，无法接水，直接跳出
            if (sz == 0) break;
            // 此时新的栈顶元素就是凹槽的左边界的下标
            int l = stk[sz - 1];
            // 可以接水的宽度（不包含左右边界本身）
            int width = r - l - 1;
            // 有效水面高度
            int bounded_height = MMIN(height[l], cur) - height[top];
            // 面积 = 宽度 * 高度，累加到总水量中
            water += width * bounded_height;
        }

        stk[sz++] = r;
    }

    return water;
}
