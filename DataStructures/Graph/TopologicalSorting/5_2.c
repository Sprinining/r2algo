#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 1005
#define MAXE 500005

int head[MAXN];
int to[MAXE];
int next[MAXE];
int edge_cnt;

// indegree[v] 记录窗口 v 当前还欠多少个“错别字”
int indegree[MAXN];
// 用来存放当前所有可盖章的窗口
int stk[MAXN];
int top;
// visit[char_pos] 标记 target 的第 char_pos 个字符是否已经变成了万能的 '?'
// 是为了防止重叠窗口对同一个字符重复清算债务，
// 确保每个字符位置有且仅有一次机会去通知邻居减入度，
// 从而避免入度被超额扣减导致逻辑崩溃。
bool visit[MAXN];

void swap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

void init_graph() {
    edge_cnt = 1;
    memset(head, 0, sizeof(head));
    memset(indegree, 0, sizeof(indegree));
    memset(visit, 0, sizeof(visit));
}

// 建立一条由“错字位置 u” 指向 “受影响窗口 v” 的有向边
void add_edge(int u, int v) {
    int edge_idx = edge_cnt++;
    next[edge_idx] = head[u];
    to[edge_idx] = v;
    head[u] = edge_idx;
    ++indegree[v];
}

int* movesToStamp(char* stamp, char* target, int* returnSize) {
    int len_s = strlen(stamp);
    int len_t = strlen(target);
    // target 中所有可能盖印章的起始位置总数
    int max_window = len_t - len_s + 1;

    init_graph();

    // 对比每个窗口和 stamp 的每一个位置
    for (int i = 0; i < max_window; ++i) {
        for (int j = 0; j < len_s; ++j) {
            // 字符对不上，就建立一条：字符绝对位置(i+j) -> 窗口起点(i) 的有向边
            if (stamp[j] != target[i + j]) add_edge(i + j, i);
        }
    }

    // 把所有入度为 0（一上来就和 stamp 完美匹配，不欠错字）的窗口压入栈
    top = 0;
    for (int i = 0; i < max_window; ++i)
        if (indegree[i] == 0) stk[top++] = i;

    int* res = malloc(sizeof(int) * max_window);
    int len = 0;

    while (top != 0) {
        int u = stk[--top];
        // 尝试把当前窗口覆盖的这 len_s 个字符都转换成万能的 '?'
        for (int i = 0; i < len_s; ++i) {
            int char_pos = i + u;  // 字符在 target 中的绝对坐标

            // 如果这个字符之前已经变成 '?'，直接跳过
            if (visit[char_pos]) continue;
            visit[char_pos] = true;

            // 通知所有依赖该字符的窗口 v
            for (int e = head[char_pos]; e > 0; e = next[e]) {
                int v = to[e];
                // 邻居窗口的错字位置减 1
                // 如果刚好减到 0，说明它也被解放了，立刻入栈
                if (--indegree[v] == 0) stk[top++] = v;
            }
        }
        res[len++] = u;
    }

    if (len != max_window) {
        *returnSize = 0;
        return NULL;
    }

    for (int l = 0, r = len - 1; l < r; ++l, --r) swap(&res[l], &res[r]);
    *returnSize = len;
    return res;
}
