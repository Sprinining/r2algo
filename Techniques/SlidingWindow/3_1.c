#include <string.h>

char* minWindow(char* s, char* t) {
    int m = strlen(s);
    int n = strlen(t);
    // t 中每种字符的个数
    int cnt[128] = {0};
    // t 中字符种数
    int kind = 0;
    for (int i = 0; i < n; ++i) {
        if (cnt[t[i]] == 0) ++kind;
        ++cnt[t[i]];
    }

    for(int l = 0, r = 0; r < m; ++r){

    }
}
