int distinctSubseqII(char* s) {
    int len = strlen(s);
    int mod = 1e9 + 7;
    // 总数（包括了空集）
    int all = 1;
    // 新增的个数
    int newAdd;
    // count[s[i] - 'a']表示以s[i]结尾的子序列个数
    int count[26] = {0};
    for (int i = 0; i < len; ++i) {
        newAdd = (all - count[s[i] - 'a'] + mod) % mod;
        all = (all + newAdd) % mod;
        count[s[i] - 'a'] = (count[s[i] - 'a'] + newAdd) % mod;
    }
    return (all - 1 + mod) % mod;
}