int max(int a, int b, int c) {
    int d = a > b ? a : b;
    return d > c ? d : c;
}

// 必须经过mid和mid+1
int maxCrossingSum(int *nums, int left, int mid, int right) {
    int leftMax = nums[mid];
    int rightMax = nums[mid + 1];

    int index = mid;
    int tempMax = 0;
    // 找左边以mid结尾的最大连续子数组的和
    while (index >= left) {
        tempMax += nums[index];
        if (tempMax > leftMax) leftMax = tempMax;
        index--;
    }

    index = mid + 1;
    tempMax = 0;
    // 找右边以mid+1开头的最大连续子数组的和
    while (index <= right) {
        tempMax += nums[index];
        if (tempMax > rightMax) rightMax = tempMax;
        index++;
    }

    return leftMax + rightMax;
}

// 分治
int maxSubArraySum(int *nums, int left, int right) {
    if (left == right) return nums[left];
    // 中偏左
    int mid = left + ((right - left) >> 1);

    // 分三类，包含所有情况
    // 第一类：以mid结尾的
    // 第二类：以mid+1开头的
    // 第三类：经过mid和mid+1的
    return max(maxSubArraySum(nums, left, mid),
               maxSubArraySum(nums, mid + 1, right),
               maxCrossingSum(nums, left, mid, right));
}


int maxSubArray(int *nums, int numsSize) {
    if (numsSize == 0) return 0;
    return maxSubArraySum(nums, 0, numsSize - 1);
}