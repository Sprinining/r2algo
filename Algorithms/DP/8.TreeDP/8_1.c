#include <string.h>

#define MAX_NODE_CNT 100001
#define MAX_EDGE_CNT 200001

typedef struct {
    long long fuel;
    int people;
} Info;

// 链式前向星
int head[MAX_NODE_CNT];
int next[MAX_EDGE_CNT];
int to[MAX_EDGE_CNT];
int edge_idx;

int seats;

void addEdge(int u, int v) {
    next[edge_idx] = head[u];
    to[edge_idx] = v;
    head[u] = edge_idx++;
}

void buildGraph(int** edges, int size) {
    edge_idx = 1;
    memset(head, 0, sizeof(*head) * MAX_NODE_CNT);
    for (int i = 0; i < size; ++i) {
        addEdge(edges[i][0], edges[i][1]);
        addEdge(edges[i][1], edges[i][0]);
    }
}

Info dfs(int u, int p) {
    if (head[u] == 0) return (Info){0, 0};
    Info info = {0, 1};
    for (int e = head[u]; e > 0; e = next[e]) {
        int v = to[e];
        // 是父结点就跳过
        if (v == p) continue;
        Info node = dfs(v, u);
        // 向上取整
        info.fuel += node.fuel + (node.people + seats - 1) / seats;
        info.people += node.people;
    }

    return info;
}

long long minimumFuelCost(int** roads, int roadsSize, int* roadsColSize, int _seats) {
    seats = _seats;
    buildGraph(roads, roadsSize);
    Info info = dfs(0, 0);
    return info.fuel;
}
