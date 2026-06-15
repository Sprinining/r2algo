int canCompleteCircuit(int* gas, int gasSize, int* cost, int costSize) {
    int n = gasSize;
    int oil = 0;
    int l = 0, r = 0;

    // 总共需要把 n 个车站纳入到窗口中
    for (int step = 0; step < n; ++step) {
        if (oil >= 0) {
            // 油量充足，右指针顺时针向前开拓
            oil += gas[r] - cost[r];
            r = (r + 1) % n;
        } else {
            // 油量破产，左指针逆时针向后倒车借油
            l = (l - 1 + n) % n;
            oil += gas[l] - cost[l];
        }
    }

    // 循环恰好走了 n 步，说明 l 和 r 已经把整个环完美合围了
    // 如果最后总油量依然小于 0，说明把全场所有的油凑一起也跑不完一圈
    return oil < 0 ? -1 : l;
}
