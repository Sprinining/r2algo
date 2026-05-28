#define MAXN 205
#define MMAX(a, b) ((a) > (b) ? (a) : (b))

typedef struct {
    int row;
    int col;
    int water_level;  // 该格子当前的最终水面高度（即 Dijkstra 中的 dist 距离）
} Cell;

int move[5] = {1, 0, -1, 0, 1};

// 全局静态内存池
Cell cells[MAXN][MAXN];

// 优先队列（小根堆）：堆数组里格只存放指向 cells 中某个格子的指针
Cell* heap[MAXN * MAXN];
int heap_sz;

void percolate_up(int top, int idx) {
    Cell* cell = heap[idx];
    int cur = idx;
    int parent = (cur - 1) >> 1;
    while (cur > top && heap[parent]->water_level > cell->water_level) {
        heap[cur] = heap[parent];
        cur = parent;
        parent = (cur - 1) >> 1;
    }
    heap[cur] = cell;
}

void heapify(int idx) {
    Cell* cell = heap[idx];
    int cur = idx;
    int lc = (cur << 1) + 1;
    while (lc < heap_sz) {
        if (lc + 1 < heap_sz &&
            heap[lc + 1]->water_level < heap[lc]->water_level)
            ++lc;
        heap[cur] = heap[lc];
        cur = lc;
        lc = (cur << 1) + 1;
    }
    heap[cur] = cell;
    percolate_up(idx, cur);
}

void push(Cell* cell) {
    heap[heap_sz++] = cell;
    percolate_up(0, heap_sz - 1);
}

Cell* pop() {
    Cell* res = heap[0];
    if (--heap_sz > 0) {
        heap[0] = heap[heap_sz];
        heapify(0);
    }
    return res;
}

int trapRainWater(int** heightMap, int heightMapSize, int* heightMapColSize) {
    int rows = heightMapSize;
    int cols = heightMapColSize[0];
    heap_sz = 0;

    // 初始化静态内存池与全图边界
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cells[i][j].row = i;
            cells[i][j].col = j;
            if (i == 0 || i == rows - 1 || j == 0 || j == cols - 1) {
                // 边界格子最终水面高度就是其自身地形高度
                cells[i][j].water_level = heightMap[i][j];
                // 作为初始木桶壁，压入小根堆
                push(&cells[i][j]);
            } else {
                // 内陆格子初始化水位为无穷大
                cells[i][j].water_level = 0x3f3f3f3f;
            }
        }
    }

    int res = 0;
    while (heap_sz > 0) {
        // 弹出当前全图木桶中水位最低的“短板”
        Cell* cell = pop();
        // 出堆时进行结算
        // 接水量 = 最终水面高度 - 原始地形高度
        res += cell->water_level - heightMap[cell->row][cell->col];

        // 探测四周的 4 个邻居
        for (int i = 0; i < 4; ++i) {
            int new_row = cell->row + move[i];
            if (new_row < 0 || new_row >= rows) continue;
            int new_col = cell->col + move[i + 1];
            if (new_col < 0 || new_col >= cols) continue;

            // 新水位取决于当前短板的水位与邻居自身地形高度的较大者
            int new_water_level =
                MMAX(heightMap[new_row][new_col], cell->water_level);

            // 松弛判定：如果算出的新水位比邻居原有的水位记录还要低，说明找到了更优解
            if (new_water_level < cells[new_row][new_col].water_level) {
                // 松弛成功，更新内存池中邻居的最优水位记录
                cells[new_row][new_col].water_level = new_water_level;
                // 将邻居作为新一代的木桶壁，塞入堆中排队排查
                push(&cells[new_row][new_col]);
            }
        }
    }

    return res;
}
