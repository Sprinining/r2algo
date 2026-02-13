int min(int a, int b) {
    return a > b ? b : a;
}

// 插入、删除、替换一个字符的代价分别为a,b,c
int editDistance(char *s1, char *s2, int a, int b, int c) {
    int len1 = strlen(s1);
    int len2 = strlen(s2);
    // dp[i][j]表示s1[前缀长度i]变成s2[前缀长度j]的最小代价
    int dp[len1 + 1][len2 + 1];
    // 空字符串到空字符串没有代价
    dp[0][0] = 0;
    // 空字符串到s2[前缀长度i]需要插入相应字符
    for (int i = 1; i <= len2; ++i)
        dp[0][i] = i * a;
    // s1[前缀长度i]到空字符串需要删除相应字符
    for (int i = 1; i <= len1; ++i)
        dp[i][0] = i * b;
    // 首行首列已经填完，剩下的格子和左侧、上方、左上方的格子有关
    for (int i = 1; i <= len1; ++i) {
        for (int j = 1; j <= len2; ++j) {
            // 1. s1[i-1]参与
            //      1.1 s1[i-1]变成s2[j-1]
            //          1.1.1 末尾字符相同，即s1[i-1]等于s2[j-1]时，代价等于dp[i-1][j-1]（情况p1）
            //          1.1.2 末尾字符不相同，代价等于dp[i-1][j-1]加上替换字符的代价（情况p2）
            //      1.2 s1[i-1]不变成s2[j-1]
            //          1.2.1 s1[0~i-1]变成s2[0~j-2]最后再插入字符s2[j-1]，代价等于dp[i][j-1]加上插入字符的代价（情况p3）
            // 2. s1[i-1]不参与
            //      2.1 即删除s1[i-1]，让s1[0~i-2]变成s2[0~j-1]，代价等于dp[i-1][j]加上删除字符的代价（情况p4）
            int p1 = 0x7fffffff;
            if (s1[i - 1] == s2[j - 1])
                p1 = dp[i - 1][j - 1];
            int p2 = 0x7fffffff;
            if (s1[i - 1] != s2[j - 1])
                p2 = dp[i - 1][j - 1] + c;
            int p3 = dp[i][j - 1] + a;
            int p4 = dp[i - 1][j] + b;
            dp[i][j] = min(min(p1, p2), min(p3, p4));
        }
    }
    return dp[len1][len2];
}

int minDistance(char *word1, char *word2) {
    return editDistance(word1, word2, 1, 1, 1);
}