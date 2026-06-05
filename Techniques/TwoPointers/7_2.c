#define ABS(x) ((x) < 0 ? -(x) : (x))

int firstMissingPositive(int* nums, int numsSize) {
    // 清除所有非正数
    // 因为找的是第一个缺失的正数，答案一定在 [1, numsSize + 1] 之间
    // 数组里原有的负数和 0 会干扰后续用负号做标记
    // 所以统一把它们改成一个不可能影响答案的大正数（numsSize + 1）
    for (int i = 0; i < numsSize; ++i) {
        if (nums[i] <= 0) nums[i] = numsSize + 1;
    }

    // 原地哈希打卡
    // 用数组元素的正负号来记录数字 [1, numsSize] 是否出现过
    // 如果数字 value 出现了，我们就去把下标为 value - 1 的位置对应的数变成负数
    for (int i = 0; i < numsSize; ++i) {
        // 获取当前位置代表的真实数值
        // 因为当前位置可能已经被前面的数字标记成负数了
        int value = ABS(nums[i]);

        // 判断这个数值是否在有效的统计范围内 [1, numsSize]
        if (value <= numsSize) {
            // 将对应下标 value - 1 的元素强制打上负号标记
            int temp = nums[value - 1];
            nums[value - 1] = -ABS(temp);
        }
    }

    for (int i = 0; i < numsSize; ++i) {
        if (nums[i] > 0) return i + 1;
    }

    return numsSize + 1;
}
