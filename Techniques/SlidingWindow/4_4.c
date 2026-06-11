int canCompleteCircuit(int* gas, int gasSize, int* cost, int costSize) {
    int n = gasSize;

    // 如果从 l 出发最远只能走到 r（在 r+1 处断油）
    // 那么带着沿途剩余油量都撑不过去，从中间任意站 [l+1, r] 起更不可能撑过去
    // 因此，[l, r] 之间的所有站点全部淘汰，下一次起点直接跳跃到 r + 1
    for (int l = 0, r = 0, oil; l < n; l = r + 1, r = l) {
        oil = 0;

        while (oil + gas[r % n] - cost[r % n] >= 0) {
            if (r - l == n) return l;
            oil += gas[r % n] - cost[r % n];
            ++r;
        }
    }

    return -1;
}
