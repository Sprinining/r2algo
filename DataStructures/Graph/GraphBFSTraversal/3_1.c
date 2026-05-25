#include <stdlib.h>
#include <string.h>

// 方向数组
int move_dir[5] = {-1, 0, 1, 0, -1};

int minimumObstacles(int** grid, int gridSize, int* gridColSize) {
    int rows = gridSize;
    int cols = gridColSize[0];
    int total_cells = rows * cols;

    // 距离表：记录从起点到每个格子的最小障碍物消除数
    int* dist = malloc(sizeof(int) * total_cells);
    // 初始将所有距离设为无穷大 (0x3f3f3f3f)
    memset(dist, 0x3f, sizeof(int) * total_cells);

    // 双端队列
    int* deque = malloc(sizeof(int) * total_cells * 2);
    int front = total_cells;
    int rear = total_cells;
    // 起点入队
    dist[0] = 0;
    deque[rear++] = 0;

    while (front < rear) {
        int idx = deque[front++];
        int row = idx / cols;
        int col = idx % cols;
        int cur_dist = dist[idx];

        // 由于 0-1 BFS 的单调性，终点第一次被弹出时，必然拿到了全局最优解
        if (row == rows - 1 && col == cols - 1) return cur_dist;

        // 遍历 4 个邻居
        for (int i = 0; i < 4; ++i) {
            int new_row = row + move_dir[i];
            if (new_row < 0 || new_row >= rows) continue;
            int new_col = col + move_dir[i + 1];
            if (new_col < 0 || new_col >= cols) continue;

            int new_idx = new_row * cols + new_col;
            int weight = grid[new_row][new_col];

            // 如果新路径算出来的代价没有比历史记录更小，直接丢弃
            if (dist[new_idx] <= cur_dist + weight) continue;

            // 发现了更优的捷径，更新距离表
            dist[new_idx] = cur_dist + weight;
            if (weight == 0) {
                // 代价为 0：极高优先级，插到队头，确保下一轮被立刻处理
                deque[--front] = new_idx;
            } else {
                // 代价为 1：正常优先级，插到队尾
                deque[rear++] = new_idx;
            }
        }
    }

    return dist[total_cells - 1];
}
