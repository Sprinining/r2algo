int canCompleteCircuit(int* gas, int gasSize, int* cost, int costSize) {
    int n = gasSize;
    int oil = 0;
    // 当前窗口实际覆盖的车站数量
    int len = 0;

    for (int l = 0, r = 0; l < n; ++l) {
        // 右边界顺时针向后扩展
        // 只要手头的油账不是负的，右指针 r 就可以继续往后探索
        while (oil >= 0) {
            // 如果窗口大小刚好等于总车站数，说明已经顺时针完美跑完一圈
            if (len == n) return l;

            oil += gas[r] - cost[r];
            r = (r + 1) % n;
            ++len;
        }

        // 右扩受阻，左边界顺时针右移止损
        --len;
        oil -= gas[l] - cost[l];
    }

    return -1;
}
