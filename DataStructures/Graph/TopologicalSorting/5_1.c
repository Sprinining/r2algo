#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// 检查 target 从 idx 开始的长度为 len_s 的子串是否能与 stamp 匹配
// 条件：1. 对应位置字符相同或者是万能匹配 '?'； 2. 不能全部都是 '?'
bool match(char* stamp, char* target, int idx, int len_s) {
    // 该窗口内是否包含至少一个非 '?' 的实际字母
    bool has_new_char = false;
    for (int i = 0; i < len_s; ++i) {
        if (target[idx + i] == '?') continue;
        // 只要有一个字母不匹配，直接返回失败
        if (target[idx + i] != stamp[i]) return false;
        has_new_char = true;
    }
    return has_new_char;
}

int* movesToStamp(char* stamp, char* target, int* returnSize) {
    int len_s = strlen(stamp);
    int len_t = strlen(target);
    // 总共可能的窗口数
    int max_windows = len_t - len_s + 1;
    int* res = (int*)malloc(sizeof(int) * max_windows);
    int len = 0;

    bool changed = true;
    while (changed) {
        changed = false;
        // 顺序遍历每一个可能的窗口起点
        for (int i = 0; i < max_windows; ++i) {
            if (match(stamp, target, i, len_s)) {
                // 记录当前逆向匹配成功的索引
                res[len++] = i;
                // 将该窗口内的所有字符替换为万能的 '?'
                for (int j = 0; j < len_s; ++j) target[i + j] = '?';
                // 标记本轮有状态更新
                changed = true;
                break;
            }
        }
    }

    // 检查最终 target 是否已经全被替换成了 '?'
    for (int i = 0; i < len_t; ++i) {
        if (target[i] != '?') {
            free(res);
            *returnSize = 0;
            // 无法完全还原，返回空指针
            return NULL;
        }
    }

    // 因为是逆向查找，所以需要将结果数组首尾反转，恢复成正向顺序
    for (int l = 0, r = len - 1; l < r; ++l, --r) swap(&res[l], &res[r]);
    *returnSize = len;
    return res;
}
