// 预处理计算 cnt 数组：i 位二进制数中无连续 1 的合法数量
void precompute(int cnt[]) {
    cnt[0] = 1;
    cnt[1] = 2;
    for (int i = 2; i <= 30; ++i) cnt[i] = cnt[i - 1] + cnt[i - 2];
}

// 递归统计 <= num 且二进制无连续 1 的数字个数
int fc(const int cnt[], int num, int i) {
    if (i == -1) return 1;

    int res = 0;
    // 当前位是 1
    if ((num & (1 << i)) != 0) {
        // 这一位设为 0，低位任意合法组合
        res += cnt[i];
        // 前一位也是 1，出现连续 1，直接返回
        if ((num & (1 << (i + 1))) != 0) {
            return res;
        }
    }
    res += fc(cnt, num, i - 1);
    return res;
}

int findIntegers(int n) {
    int cnt[31] = {0};
    precompute(cnt);
    return fc(cnt, n, 30);
}
