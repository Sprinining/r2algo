#define MAXL 10

int cnt[MAXL];
int num;

/*
    当前已经确定了一部分前缀，并且：
    1. 当前前缀和 num 的前缀完全相同
    2. 前缀一定不为空
    3. 还剩 len 位没有填
    4. status 表示已经使用过哪些数字（位运算状态压缩）
    返回在满足“不出现重复数字”的情况下，后续还能组成多少个合法数字
*/
int dfs(int len, int offset, int status) {
    // 所有位都填完了，当前形成的数字本身就是一种合法方案
    if (len == 0) return 1;

    int res = 0;
    int cur = (num / offset) % 10;

    // 枚举当前位填比 cur 小的数字
    // 因为前缀之前一直相等，只要这一位比 cur 小，后面的位就可以随便排列了
    for (int i = 0; i < cur; ++i)
        if ((status & (1 << i)) == 0) res += cnt[len - 1];

    // 尝试当前位继续填 cur，这样才能继续保持“前缀相等”
    if ((status & (1 << cur)) == 0) {
        res += dfs(len - 1, offset / 10, status | (1 << cur));
    }

    return res;
}

int countSpecialNumbers(int n) {
    // n 的位数
    int len = 1;
    // 最高位对应的权值
    int offset = 1;
    int temp = n / 10;
    while (temp > 0) {
        ++len;
        offset *= 10;
        temp /= 10;
    }

    /*
        cnt[i] 含义：当前已经确定了一部分前缀，还剩 i 位没有填时，
        后续能组成多少种“不重复数字”的排列
        举例：
        len = 4
        cnt[3] = 9 * 8 * 7
        cnt[2] = 8 * 7
        cnt[1] = 7
        cnt[0] = 1
    */
    cnt[0] = 1;
    for (int i = 1, k = 10 - len + 1; i < len; ++i, ++k) {
        cnt[i] = cnt[i - 1] * k;
    }

    int res = 0;
    /*
        先统计位数 < len 的所有合法数字
        1 位数：1~9，共 9 个
        2 位数：9 * 9
        3 位数：9 * 9 * 8
        ...
    */
    if (len >= 2) {
        // 1 位数
        res = 9;
        // a: 当前长度的方案数
        // b: 后续可选数字数量
        for (int i = 2, a = 9, b = 9; i < len; ++i, --b) {
            a *= b;
            res += a;
        }
    }

    num = n;
    // 接下来统计位数 == len 的合法数字
    // num 的最高位
    int first = n / offset;
    res += (first - 1) * cnt[len - 1];
    // 最高位等于 num 的情况继续递归处理后续位
    res += dfs(len - 1, offset / 10, 1 << first);

    return res;
}
