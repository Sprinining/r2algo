int canCompleteCircuit(int* gas, int gasSize, int* cost, int costSize) {
    int n = gasSize;
    int oil = 0;
    int len = n << 1;

    // 外循环为 r
    for (int l = n, r = n; r < len; ++r) {
        oil += gas[r % n] - cost[r % n];
        while (oil < 0 && r - l + 1 < n) {
            // l 向左扩
            --l;
            oil += gas[l % n] - cost[l % n];
        }

        // 此时的 oil 代表的是全场总油量 - 全场总消耗
        // oil 小于 0 的时候，不管怎么调整出发顺序都是无解的
        if (r - l + 1 == n) return oil < 0 ? -1 : l % n;
    }

    return -1;
}
