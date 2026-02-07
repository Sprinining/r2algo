int max(int a, int b) {
    return a > b ? a : b;
}

// 返回下标left~right的最长回文子序列长度
int recursive(char *s, int left, int right) {
//    if (left > right) return 0;   
    // 只有一个元素
    if (left == right) return 1;
    // 只有两个元素
    if (left + 1 == right) return s[left] == s[right] ? 2 : 1;
    if (s[left] == s[right]) {
        return recursive(s, left + 1, right - 1) + 2;
    } else {
        return max(recursive(s, left, right - 1), recursive(s, left + 1, right));
    }
}

// 暴力超时
int longestPalindromeSubseq(char *s) {
    return recursive(s, 0, strlen(s) - 1);
}