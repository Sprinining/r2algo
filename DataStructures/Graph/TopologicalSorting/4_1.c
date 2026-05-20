#include <stdlib.h>
#include <string.h>

#define MAXN 26
#define MAXE 100
#define MMIN(a, b) ((a) > (b) ? (b) : (a))

int head[MAXN];
int to[MAXE];
int next[MAXE];
int edge_cnt;
int indegree[MAXN];

int stk[MAXN];
int top;

void init_graph(char** words, int wordsSize) {
    edge_cnt = 1;
    memset(head, 0, sizeof(head));
    // -1 表示没出现过
    memset(indegree, -1, sizeof(indegree));
    // 所有出现过的字符入度置零
    for (int i = 0; i < wordsSize; ++i) {
        char* s = words[i];
        int len_s = strlen(s);
        for (int j = 0; j < len_s; ++j) indegree[s[j] - 'a'] = 0;
    }
}

void add_edge(int u, int v) {
    int edge_idx = edge_cnt++;
    next[edge_idx] = head[u];
    to[edge_idx] = v;
    head[u] = edge_idx;
    ++indegree[v];
}

char* alienOrder(char** words, int wordsSize) {
    init_graph(words, wordsSize);

    // 生成图
    for (int i = 1; i < wordsSize; ++i) {
        char* pre = words[i - 1];
        char* cur = words[i];
        int len_pre = strlen(pre);
        int len_cur = strlen(cur);
        int len_min = MMIN(len_pre, len_cur);
        int j = 0;
        while (j < len_min && pre[j] == cur[j]) ++j;
        if (j == len_min) {
            // 前缀一致
            // pre 比 cur 短或者一样长
            if (len_pre <= len_cur) continue;
            // pre 比 cur 长，不是合法字典
            return "";
        }
        // pre[j] 字典序在 cur[j] 前面
        add_edge(pre[j] - 'a', cur[j] - 'a');
    }

    // 出现的字符种数
    int kinds = 0;
    for (int i = 0; i < MAXN; ++i)
        if (indegree[i] != -1) ++kinds;

    // 初始状态入度为零的入栈
    top = 0;
    for (int i = 0; i < MAXN; ++i)
        if (indegree[i] == 0) stk[top++] = i;

    // 得到拓扑序列
    char* res = malloc(sizeof(char) * (MAXN + 1));
    int len = 0;
    while (top != 0) {
        int u = stk[--top];
        for (int e = head[u]; e > 0; e = next[e]) {
            int v = to[e];
            if (--indegree[v] == 0) stk[top++] = v;
        }
        res[len++] = u + 'a';
    }
    res[len] = '\0';

    return len == kinds ? res : "";
}
