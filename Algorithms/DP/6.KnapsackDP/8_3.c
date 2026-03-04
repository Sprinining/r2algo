#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 最大物品数
#define MAXN 1001
// 最大的原始组编号
#define MAXCNT 10001

int mmax(int a, int b) { return a > b ? a : b; }

// 链式前向星
typedef struct {
    int cost;
    int weight;
    int next;
} Edge;

Edge edges[MAXN];
// 顶点序号从 0 开始
int heads[MAXCNT];
// 边的序号从 1 开始，0 表示没有边
int edge_cnt;

void init() {
    // 边序号从 1 开始
    edge_cnt = 0;
    memset(heads, 0, sizeof(heads));
}

// 只关心边的起点 u，不关心终点 v
void addEdge(int u, int cost, int weight) {
    ++edge_cnt;
    edges[edge_cnt].cost = cost;
    edges[edge_cnt].weight = weight;
    // 头插法
    edges[edge_cnt].next = heads[u];
    heads[u] = edge_cnt;
}

// 原始组号到新组号的映射，也就是原来顶点序号到新的顶点序号的映射
int map[MAXCNT + 1];

int main() {
    init();
    int m, n;
    scanf("%d %d", &m, &n);
    memset(map, -1, sizeof(map));
    int node_cnt = 0;

    for (int i = 0, a, b, c; i < n; ++i) {
        scanf("%d%d%d", &a, &b, &c);
        // 组号离散化，变成从 0 开始的连续编号
        if (map[c] == -1) map[c] = node_cnt++;
        addEdge(map[c], a, b);
    }

    int rows = node_cnt + 1;
    int cols = m + 1;
    int* dp = calloc(cols, sizeof(*dp));

    // 行号 = 组号 = 顶点号
    for (int i = 1; i < rows; ++i) {
        for (int j = cols - 1; j > 0; --j) {
            int p = dp[j];
            for (int ei = heads[i - 1]; ei != 0; ei = edges[ei].next) {
                int cost = edges[ei].cost;
                int weight = edges[ei].weight;
                if (cost <= j) p = mmax(p, dp[j - cost] + weight);
            }
            dp[j] = p;
        }
    }

    printf("%d", dp[cols - 1]);
}