int canCompleteCircuit(int* gas, int gasSize, int* cost, int costSize) {
    int n = gasSize;
    int oil = 0;
    int len = n << 1;

    // 外循环为 r
    for (int l = 0, r = 0; r < len; ++r) {
        oil += gas[r % n] - cost[r % n];

        while (oil < 0) {
            oil -= gas[l % n] - cost[l % n];
            ++l;
        }

        if (r - l + 1 == n) return l;
    }

    return -1;
}
