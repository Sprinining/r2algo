int findDuplicate(int* nums, int numsSize) {
    int slow = 0, fast = 0;
    // 严格按照 1:2 的速度差初始化
    // slow 走 1 步到达 nums[0]
    slow = nums[slow];
    // fast 走 2 步到达 nums[nums[0]]
    fast = nums[nums[fast]];

    // 快慢指针在环内相遇
    while (slow != fast) {
        slow = nums[slow];
        fast = nums[nums[fast]];
    }

    // 寻找环的入口（即重复的数字）
    fast = 0;
    while (slow != fast) {
        slow = nums[slow];
        fast = nums[fast];
    }

    return fast;
}
