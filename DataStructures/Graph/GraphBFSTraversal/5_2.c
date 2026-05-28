#include <stdbool.h>

#define MAXN 205
#define MMAX(a, b) ((a) > (b) ? (a) : (b))

typedef struct {
    int row;
    int col;
    int water_level;  // 格子的最终水面高度
    // 解耦内陆初始化对 0x3f3f3f3f 哨兵值的依赖
    // 让邻居探测直接退化为最快的布尔短路拦截，不再进行冗余的数学松弛计算
    bool visit;  // 标记该格子是否已经入过堆
} Cell;

int move[5] = {1, 0, -1, 0, 1};
Cell cells[MAXN][MAXN];
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

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cells[i][j].row = i;
            cells[i][j].col = j;
            if (i == 0 || i == rows - 1 || j == 0 || j == cols - 1) {
                cells[i][j].water_level = heightMap[i][j];
                cells[i][j].visit = true;
                push(&cells[i][j]);
            } else {
                // 内陆格子尚未触及，统一初始化为 false
                // 不需要管内陆格子的 water_level 初始值
                cells[i][j].visit = false;
            }
        }
    }

    int res = 0;

    while (heap_sz > 0) {
        // 弹出当前全图木桶中水位最低的“短板”
        Cell* cell = pop();
        // 蓄水量 = 最终确定的水面高度 - 原始地形高度
        res += cell->water_level - heightMap[cell->row][cell->col];

        for (int i = 0; i < 4; ++i) {
            int new_row = cell->row + move[i];
            if (new_row < 0 || new_row >= rows) continue;
            int new_col = cell->col + move[i + 1];
            if (new_col < 0 || new_col >= cols) continue;

            // 因为小根堆每次弹出的短板水位是单调递增的。
            // 当一个内陆格子第一次被某个方向推过来的水波触碰到时，它见到的就是能圈住它的绝对最优解
            // 如果邻居已经 visit == true，说明它早就确定过了
            if (cells[new_row][new_col].visit) continue;
            cells[new_row][new_col].visit = true;

            // 邻居能达到的水位，取决于当前短板水位和邻居自身地形高度的较大者
            int new_water_level =
                MMAX(heightMap[new_row][new_col], cell->water_level);
            // 更新邻居的水位记录
            cells[new_row][new_col].water_level = new_water_level;
            // 邻居带上最终确定的水位入堆，准备作为下一代更深入的木桶壁
            push(&cells[new_row][new_col]);
        }
    }

    return res;
}
