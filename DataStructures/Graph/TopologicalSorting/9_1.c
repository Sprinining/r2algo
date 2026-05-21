#include <string.h>

#define MMAX(a, b) ((a) > (b) ? (a) : (b))

#define MAX_N 100005

int indegree[MAX_N];
// 存储游离链延伸到当前节点的最长路径长度（不包含当前节点本身）
int deep[MAX_N];
int queue[MAX_N];
int l, r;

void init(int n) {
    memset(indegree, 0, sizeof(int) * n);
    memset(deep, 0, sizeof(int) * n);
    l = 0;
    r = 0;
}

int maximumInvitations(int* favorite, int favoriteSize) {
    int n = favoriteSize;
    init(n);

    // 统计每个节点的入度
    // i 指向 favorite[i] 的一条有向边
    for (int i = 0; i < n; ++i) ++indegree[favorite[i]];

    for (int i = 0; i < n; ++i)
        if (indegree[i] == 0) queue[r++] = i;

    // 剪掉图中的所有非环分支（即“游离链”），只留下基环
    while (l < r) {
        int u = queue[l++];
        int v = favorite[u];

        // 剪掉 u 之后，如果 v 的入度变为 0，说明 v 也在游离链上，继续入队
        if (--indegree[v] == 0) queue[r++] = v;
        // 递推更新到达节点 v 的最长外接链条的长度
        deep[v] = MMAX(deep[v], deep[u] + 1);
    }

    // 记录所有“大小为 2 的环”及其外接最长链的总节点数之和
    int sum_of_small_ring = 0;
    // 记录所有“大小大于 2 的环”中的最大环长度
    int max_large_ring = 0;

    // 遍历所有节点，寻找并处理图中的各个环
    for (int i = 0; i < n; ++i) {
        // 跳过入度为 0 的节点（已被拓扑排序剪掉，不在环上）
        if (indegree[i] == 0) continue;

        // 标记当前节点已访问（通过将入度清零），开始计算当前环的长度
        indegree[i] = 0;
        int ring_len = 1;
        int v = favorite[i];

        // 沿着喜欢关系遍历整个环，并清除环上节点的入度标记
        while (indegree[v] != 0) {
            ++ring_len;
            indegree[v] = 0;
            v = favorite[v];
        }

        // 根据环的大小分情况讨论
        if (ring_len == 2) {
            // 情况 1：基环大小为 2
            // 这种“小双向环”两端都可以挂载最长的游离链，并且多个这样独立的结构可以同时安排在同一张圆桌上
            // 能够容纳的节点数 = 环本身的 2 个节点 + 节点 i 延伸出去的最长链 +
            // 节点 favorite[i] 延伸出去的最长链
            sum_of_small_ring += deep[i] + deep[favorite[i]] + 2;
        } else {
            // 情况 2：基环大小大于 2
            // 这种“大环”内部是有向单向流动的，无法在圆桌上外接完整的链，也无法与其他环共存
            // 圆桌上只能坐这一个大环上的所有人，因此取最大的一个环
            max_large_ring = MMAX(max_large_ring, ring_len);
        }
    }

    return MMAX(sum_of_small_ring, max_large_ring);
}
