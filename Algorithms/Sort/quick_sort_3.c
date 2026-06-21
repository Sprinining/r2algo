void swap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

void quick_sort(int* nums, int left, int right) {
    if (left >= right) return;

    // 确保左端点的值 <= 右端点的值，作为两个轴
    if (nums[left] > nums[right]) swap(&nums[left], &nums[right]);
    int pivot1 = nums[left];
    int pivot2 = nums[right];

    int l = left;
    int r = right;
    int k = l + 1;

    while (k < r) {
        if (nums[k] > pivot1 && nums[k] < pivot2) {
            // 属于中间区间，直接跳过
            ++k;
        } else if (nums[k] <= pivot1) {
            // 属于左边区间，和左边界交换，两个指针同时推进
            swap(&nums[++l], &nums[k++]);
        } else {
            // 属于右边区间，从右边找一个不属于右边区间的数换过来
            while (k < r && nums[r] >= pivot2) --r;
            swap(&nums[k], &nums[r]);
            // 注意：这里没有 ++k，因为从右边换过来的数还需要在下一轮重新判断
        }
    }

    // 将两个基准数归位
    swap(&nums[left], &nums[l]);
    swap(&nums[right], &nums[r]);

    // 对划分出的三个区间分别进行递归排序
    quick_sort(nums, left, l - 1);
    quick_sort(nums, l + 1, r - 1);
    quick_sort(nums, r + 1, right);
}

int* sortArray(int* nums, int numsSize, int* returnSize) {
    *returnSize = numsSize;
    quick_sort(nums, 0, numsSize - 1);
    return nums;
}
