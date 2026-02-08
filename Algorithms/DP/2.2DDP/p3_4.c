int max(int a, int b) { return a > b ? a : b; }

// 空间压缩
int longestPalindromeSubseq(char* s) {
    int len = strlen(s);
    int* dp = (int*)malloc(sizeof(int) * len);
    // 左下角元素
    int leftDown;
    for (int left = len - 1; left >= 0; left--) {
        // dp[left][left]
        dp[left] = 1;
        // 主对角线上方的一条斜线
        if (left + 1 < len) {
            // 记录下左下角
            leftDown = dp[left + 1];
            // dp[left][left+1]
            dp[left + 1] = s[left] == s[left + 1] ? 2 : 1;
        }
        // 上三角的其他位置，之和左边、下边、左下角相关
        for (int right = left + 2; right < len; ++right) {
            int backup = dp[right];
            if (s[left] == s[right])
                dp[right] = leftDown + 2;
            else
                // 没更新前，dp[right]表示dp[left+1][right]，dp[right-1]表示dp[left][right-1]
                dp[right] = max(dp[right], dp[right - 1]);
            leftDown = backup;
        }
    }

    return dp[len - 1];
}