#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 55
#define INF 0x3f3f3f3f

// 邻接表：包含字符 i+'a' 的贴纸在 stickers 中的下标
int contains[26][MAXN];
// 包含字符 i+'a' 的贴纸个数
int c_lens[26];
// cnts[i][j] = stickers[i] 中字符 j+'a' 的个数
int cnts[MAXN][26];
// left[i] = target 中字符 i+'a' 未处理掉的个数
int left[26];
// target 中未处理掉的字符种数
int kinds;

// --- 记忆化哈希表实现 ---
// 由于状态数可能较多，我们用一个简易的链地址法哈希表来记录已经计算过的 left
// 状态
#define HASH_SIZE 9973

typedef struct HashNode {
    char key[30];  // 压缩后的状态字符串，例如 "a2b1c3"
    int val;       // 该状态对应的最小贴纸数
    struct HashNode* next;
} HashNode;

HashNode* hashTable[HASH_SIZE];

// 将当前的 left 数组压缩成一个唯一的字符串作为 Key
void getStateKey(int* current_left, char* key) {
    int p = 0;
    for (int i = 0; i < 26; i++) {
        if (current_left[i] > 0) {
            p += sprintf(key + p, "%c%d", i + 'a', current_left[i]);
        }
    }
    if (p == 0) strcpy(key, "empty");
}

// 哈希函数
unsigned int hash(char* str) {
    unsigned int h = 0;
    while (*str) {
        h = h * 31 + *str++;
    }
    return h % HASH_SIZE;
}

// 查找记忆化结果
int hashFind(char* key) {
    unsigned int h = hash(key);
    HashNode* node = hashTable[h];
    while (node) {
        if (strcmp(node->key, key) == 0) return node->val;
        node = node->next;
    }
    return -1;
}

// 插入记忆化结果
void hashInsert(char* key, int val) {
    unsigned int h = hash(key);
    HashNode* node = (HashNode*)malloc(sizeof(HashNode));
    strcpy(node->key, key);
    node->val = val;
    node->next = hashTable[h];
    hashTable[h] = node;
}

// 清理哈希表内存
void freeHashTable() {
    for (int i = 0; i < HASH_SIZE; i++) {
        HashNode* node = hashTable[i];
        while (node) {
            HashNode* tmp = node;
            node = node->next;
            free(tmp);
        }
        hashTable[i] = NULL;
    }
}
// ------------------------

// 核心 DFS 搜索函数
int dfs(int n) {
    char key[30];
    getStateKey(left, key);

    // 如果所有字符都消完了，不需要贴纸
    if (strcmp(key, "empty") == 0) return 0;

    // 检查记忆化
    int cached = hashFind(key);
    if (cached != -1) return cached;

    // 贪心策略：总是试图消去当前 target 中剩余的第一个字符
    // 这对应了你 C++ 版本中对 str[0] 的处理，能极大减少搜索分支
    int first_ch = -1;
    for (int i = 0; i < 26; i++) {
        if (left[i] > 0) {
            first_ch = i;
            break;
        }
    }

    // 如果找不到任何剩余字符（理论上前面 empty 已经拦截了）
    if (first_ch == -1) return 0;

    int ans = INF;

    // 顺着你的思路：遍历所有包含 first_ch 的贴纸
    for (int j = 0; j < c_lens[first_ch]; ++j) {
        int idx = contains[first_ch][j];  // 贴纸的下标

        // 备份当前的 left 状态，用于回溯
        int bak_left[26];
        memcpy(bak_left, left, sizeof(left));

        // 尝试用这枚贴纸去消减 left 里的字符
        for (int k = 0; k < 26; ++k) {
            if (left[k] > 0 && cnts[idx][k] > 0) {
                left[k] -= cnts[idx][k];
                if (left[k] < 0) left[k] = 0;
            }
        }

        // 递归进入下一层
        int next_res = dfs(n);
        if (next_res != -1) {
            if (next_res + 1 < ans) {
                ans = next_res + 1;
            }
        }

        // 回溯状态
        memcpy(left, bak_left, sizeof(left));
    }

    // 如果最终 ans 没有被更新，说明无解
    int final_res = (ans == INF) ? -1 : ans;
    hashInsert(key, final_res);
    return final_res;
}

int minStickers(char** stickers, int stickersSize, char* target) {
    int n = stickersSize;
    int m = strlen(target);

    // 初始化 target 相关的辅助变量
    memset(left, 0, sizeof(left));
    kinds = 0;
    for (int i = 0; i < m; ++i) {
        char ch = target[i];
        if (left[ch - 'a'] == 0) ++kinds;
        ++left[ch - 'a'];
    }

    // 初始化 stickers 相关的辅助变量
    memset(cnts, 0, sizeof(cnts));
    memset(contains, -1, sizeof(contains));
    memset(c_lens, 0, sizeof(c_lens));
    for (int i = 0; i < n; ++i) {
        char* s = stickers[i];
        int len = strlen(s);
        for (int j = 0; j < len; ++j) {
            int ch = s[j];
            if (cnts[i][ch - 'a'] == 0)
                contains[ch - 'a'][c_lens[ch - 'a']++] = i;
            ++cnts[i][ch - 'a'];
        }
    }

    // 在开始搜索前，先做一次可行性检查：
    // 如果 target 中的某个字符，在所有贴纸里都找不到，直接返回 -1
    for (int i = 0; i < 26; i++) {
        if (left[i] > 0 && c_lens[i] == 0) {
            return -1;
        }
    }

    // 初始化哈希表
    memset(hashTable, 0, sizeof(hashTable));

    int result = dfs(n);

    // 释放动态内存
    freeHashTable();

    return result;
}
