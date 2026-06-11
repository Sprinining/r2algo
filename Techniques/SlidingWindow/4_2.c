int canCompleteCircuit(int* gas, int gasSize, int* cost, int costSize) {
    int n = gasSize;

    // 记录当前窗口（从 l 到 r-1 顺时针方向）内的累计剩余油量
    int oil = 0;
    // l 为尝试的起点，r 为当前探索到的终点
    int l = 0, r = 0;

    do {
        // r 指针顺时针向后扩展
        oil += gas[r] - cost[r];
        r = (r + 1) % n;

        // 如果油不够了，l 指针逆时针向前追溯借油
        // 只要当前油量为负，且起点和终点还没有碰头，就尝试通过提前出发来补油
        while (oil < 0 && l != r) {
            l = (l - 1 + n) % n;
            oil += gas[l] - cost[l];
        }
    } while (l != r);

    // 循环结束时，如果 oil 依然小于 0
    // 说明把所有的油都凑在一起也跑不完一圈，返回 -1
    // 如果 oil >= 0，说明最后收缩出来的起点 l 是一个合法的起点，返回 l
    return oil < 0 ? -1 : l;
}
