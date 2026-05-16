#define MAXN 300

int father[MAXN * MAXN];
int rank[MAXN * MAXN];
int sets;

void build(int n) {
    for (int i = 0; i < n; ++i) {
        father[i] = i;
        rank[i] = 1;
    }
    sets = n;
}

int find(int x) {
    if (father[x] == x) return x;
    return father[x] = find(father[x]);
}

void unite(int a, int b) {
    int fa = find(a);
    int fb = find(b);
    if (fa == fb) return;
    if (rank[fa] > rank[fb]) {
        father[fb] = fa;
    } else if (rank[fa] < rank[fb]) {
        father[fa] = fb;
    } else {
        father[fb] = fa;
        ++rank[fa];
    }
    --sets;
}

int numIslands(char** grid, int gridSize, int* gridColSize) {
    int rows = gridSize;
    int cols = gridColSize[0];

    build(rows * cols);

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (grid[i][j] == '0') {
                --sets;
                continue;
            }
            if (j > 0 && grid[i][j - 1] == '1') unite(i * cols + j, i * cols + j - 1);
            if (i > 0 && grid[i - 1][j] == '1') unite(i * cols + j, (i - 1) * cols + j);
        }
    }
    return sets;
}
