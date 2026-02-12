// 空间优化
int numDistinct(char* s, char* t) {
    const int MOD = 1e9 + 7;
    int lenS = strlen(s);
    int lenT = strlen(t);
    // dp[i][j]表示在s中前缀长度为i的字符串所包含的所有子序列中，有多少个子序列等于t中前缀长度为j的字符串
    // i、j表示前缀长度，而不是字符串中的下标
    int dp[lenT + 1];
    // 第一列全1，表示空串的时候匹配
    // 第一行除了第一个元素，全0，不可能匹配
    memset(dp, 0, sizeof(int) * (lenT + 1));
    dp[0] = 1;

    // 当前位置依赖于左上角和上方的格子，所以从上往下，从右往左填
    for (int i = 1; i <= lenS; ++i) {
        for (int j = lenT; j >= 1; j--) {
            // 情况1：s[i]不选，则问题转化为dp[i -
            // 1][j]，即上方格子，此时dp[j]不用变动，直接就表示上方格子
            // 情况2：s[i]选，但是前提条件是末尾字符相同，问题转化为dp[i - 1][j
            // - 1]，dp[j-1]尚未更新，表示左上方格子
            if (s[i - 1] == t[j - 1]) dp[j] = (dp[j] + dp[j - 1]) % MOD;
        }
    }
    return dp[lenT];
}