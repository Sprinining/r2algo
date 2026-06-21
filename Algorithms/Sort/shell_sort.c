void shell_sort(int* nums, int n) {
    // 外层循环：控制步长 gap，初始为数组长度的一半，每次折半，直到步长为 1
    for (int gap = n / 2; gap > 0; gap /= 2) {
        // 内层循环：对每个按照 gap 分组的子序列进行插入排序
        // i 从 gap 开始，逐个往后遍历，相当于交替处理各个分组
        for (int i = gap; i < n; ++i) {
            // 当前需要往前插入的元素
            int temp = nums[i];
            int j = i;

            // 往回找插入位置（只和同组的元素比较：下标差值为 gap）
            // 如果前面的元素更大，就把它往后挪一个 gap 的位置
            while (j >= gap && nums[j - gap] > temp) {
                nums[j] = nums[j - gap];
                j -= gap;
            }

            // 找到合适的位置，把当前元素填进去
            nums[j] = temp;
        }
    }
}

int* sortArray(int* nums, int numsSize, int* returnSize) {
    *returnSize = numsSize;
    shell_sort(nums, numsSize);
    return nums;
}
