typedef long long ll;

// 统计数字 d 在 [1, num] 范围中出现的次数
ll count(int num, int d) {
    ll res = 0;

    // right 表示当前位右边的情况数
    for (ll right = 1, temp = num; temp != 0; right *= 10, temp /= 10) {
        // left 表示当前位左边的情况数
        ll left = temp / 10;
        // 当前位的数字（正在处理的位）
        ll cur = temp % 10;

        // 处理前导 0 的情况（不能以 0 开头，所以需要特殊减 1）
        if (d == 0) --left;

        // 当前这一位上，数字 d 出现的可能数
        res += left * right;

        if (cur > d) {
            // 如果当前位数字大于 d，那么右边可以从 0 枚举到 999...，即全加一轮 right
            res += right;
        } else if (cur == d) {
            // 如果当前位等于 d，那么右边可以取值的范围是 [0, 右边真实数值]
            res += num % right + 1;
        }
        // 如果 cur < d，当前这一位上就不能再出现 d，不做额外加法
    }

    return res;
}

// 返回 1~n 中数字 1 出现的次数
int countDigitOne(int n) { return (int)count(n, 1); }
