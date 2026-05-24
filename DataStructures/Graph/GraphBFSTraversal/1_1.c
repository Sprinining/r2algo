#define MAXN 100

int queue[MAXN * MAXN][2];
int front, rear;
int dir[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

int maxDistance(int** grid, int gridSize, int* gridColSize) {
    int n = gridSize;
    front = 0;
    rear = 0;

    // 多源 BFS，所有陆地先入队列
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (grid[i][j] == 1) {
                queue[rear][0] = i;
                queue[rear][1] = j;
                ++rear;
                // 访问过的标记成 -1
                grid[i][j] = -1;
            }
        }
    }

    // 全是陆地或者海洋
    int cnt = rear - front;
    if (cnt == 0 || cnt == n * n) return -1;

    int level = 0;
    // 从陆地往外层序便利
    while (front < rear) {
        // 当前层有 sz 个节点
        int sz = rear - front;
        ++level;

        // 一层一层的弹出
        for (int i = 0; i < sz; ++i) {
            int row = queue[front][0];
            int col = queue[front][1];
            ++front;
            // 四个方向
            for (int j = 0; j < 4; ++j) {
                int new_row = row + dir[j][0];
                if (new_row < 0 || new_row >= n) continue;
                int new_col = col + dir[j][1];
                if (new_col < 0 || new_col >= n) continue;
                // 访问过的就跳过
                if (grid[new_row][new_col] == -1) continue;
                grid[new_row][new_col] = -1;
                // 下一层入队列
                queue[rear][0] = new_row;
                queue[rear][1] = new_col;
                ++rear;
            }
        }
    }

    return level - 1;
}
