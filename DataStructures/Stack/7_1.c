#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

char* removeDuplicateLetters(char* s) {
    int len = strlen(s);

    // 频率数组：记录每个字符在字符串中总共出现的次数
    int cnt[26];
    memset(cnt, 0, sizeof(cnt));
    for (int i = 0; i < len; ++i) ++cnt[s[i] - 'a'];

    int stk[26];
    int sz = 0;

    // 标记数组：记录某个字符当前是否已经存在于栈中
    bool in_stk[26];
    memset(in_stk, 0, sizeof(in_stk));

    for (int i = 0; i < len; ++i) {
        int cur = s[i] - 'a';
        // 该字符在未处理序列中的剩余可用次数减 1
        --cnt[cur];

        // 如果当前字符已经在栈中，说明它已经在前面找到了一个极佳的排位
        // 直接跳过，既避免重复，又保护了栈里现有的完美顺序
        if (in_stk[cur]) continue;

        // 栈顶元素大于当前元素，弹出它能让当前更小的字符靠前，字典序更小
        while (sz > 0 && stk[sz - 1] > cur && cnt[stk[sz - 1]] > 0) {
            in_stk[stk[sz - 1]] = false;
            --sz;
        }

        stk[sz++] = cur;
        in_stk[cur] = true;
    }

    char* res = malloc(sizeof(char) * (sz + 1));
    for (int i = 0; i < sz; ++i) res[i] = stk[i] + 'a';
    res[sz] = '\0';

    return res;
}
