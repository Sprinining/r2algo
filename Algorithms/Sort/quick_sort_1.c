void swap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

void quick_sort(int* nums, int left, int right) {
    if (left >= right) return;

    // 选中间的和最左侧交换
    int mid = left + ((right - left) >> 1);
    swap(&nums[left], &nums[mid]);
    int pivot = nums[left];
    int l = left, r = right;

    // 交换法
    while (l < r) {
        while (l < r && nums[r] >= pivot) --r;
        while (l < r && nums[l] <= pivot) ++l;
        if (l < r) swap(&nums[l], &nums[r]);
    }
    // 交换法最后的交换之所以绝对正确
    // 是因为寻找较小值的右指针 r 总是被规定先移动
    // 这保证了无论两个指针如何相遇，相遇点的值都一定小于或等于基准数
    // 因此将其换回最左侧永远安全
    swap(&nums[left], &nums[l]);

    quick_sort(nums, left, l - 1);
    quick_sort(nums, l + 1, right);
}

int* sortArray(int* nums, int numsSize, int* returnSize) {
    *returnSize = numsSize;
    quick_sort(nums, 0, numsSize - 1);
    return nums;
}
