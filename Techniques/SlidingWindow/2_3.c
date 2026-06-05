#include <stdbool.h>
#include <string.h>

#define MMAX(a, b) ((a) > (b) ? (a) : (b))

// 用一个布尔数组记录字符是否在当前窗口中，初始化全为 false
bool entered[128];

int lengthOfLongestSubstring(char* s) {
    int n = strlen(s);
    memset(entered, 0, sizeof(entered));
    int res = 0;

    for (int l = 0, r = 0; r < n; r++) {
        char ch = s[r];

        // 如果新来的字符 ch 已经在窗口里了
        // 左指针 l 必须向右收缩，一边走一边把路过的字符标记为 false
        // 直到把窗口里那个旧的 ch 剔除出去，循环才会终止
        while (entered[ch]) {
            entered[s[l]] = false;
            ++l;
        }

        // 此时，旧的 ch 已经被踢出去了
        // 可以安全地把新的 ch 标记为 true，放入窗口中
        entered[ch] = true;

        res = MMAX(res, r - l + 1);
    }

    return res;
}
