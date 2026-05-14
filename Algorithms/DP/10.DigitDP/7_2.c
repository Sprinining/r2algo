int findIntegers(int n) {
    int cnt[31] = {0};
    cnt[0] = 1;
    cnt[1] = 2;
    // 预处理斐波那契数组
    for (int i = 2; i <= 30; ++i) cnt[i] = cnt[i - 1] + cnt[i - 2];

    int res = 0;
    // 从高位 30 向下遍历
    for (int i = 30; i >= -1; --i) {
        if (i == -1) {
            ++res;
            break;
        }
        // 当前位是 1
        if ((n & (1 << i)) != 0) {
            res += cnt[i];
            // 出现连续 1，直接退出
            if ((n & (1 << (i + 1))) != 0) break;
        }
    }
    return res;
}
