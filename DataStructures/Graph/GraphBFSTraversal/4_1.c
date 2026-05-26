#include <string.h>

#define MAXL 10005

int dir[5][2] = {{0, 0}, {0, 1}, {0, -1}, {1, 0}, {-1, 0}};
int front, rear;
// 扁平化
int deque[MAXL << 1];
int dist[MAXL];

int minCost(int** grid, int gridSize, int* gridColSize) {
    int rows = gridSize;
    int cols = gridColSize[0];

    memset(dist, 0x3f, sizeof(dist));
    front = MAXL;
    rear = MAXL;
    deque[rear++] = 0;
    dist[0] = 0;

    while (front < rear) {
        int idx = deque[front++];
        int row = idx / cols;
        int col = idx % cols;
        int cur_dist = dist[idx];
        if (row == rows - 1 && col == cols - 1) return dist[idx];

        for (int i = 1; i <= 4; ++i) {
            int new_row = row + dir[i][0];
            if (new_row < 0 || new_row >= rows) continue;
            int new_col = col + dir[i][1];
            if (new_col < 0 || new_col >= cols) continue;

            // 从 [row][col] 到 [new_row][new_col] 要不要代价
            int weight = grid[row][col] == i ? 0 : 1;
            int new_idx = new_row * cols + new_col;
            // 可以变得更短
            if (dist[new_idx] > cur_dist + weight) {
                dist[new_idx] = cur_dist + weight;
                if (weight == 0) {
                    // 不需要代价的移动，优先级更高
                    deque[--front] = new_idx;
                } else {
                    deque[rear++] = new_idx;
                }
            }
        }
    }

    return dist[rows * cols - 1];
}
