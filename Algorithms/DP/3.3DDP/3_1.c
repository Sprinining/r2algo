#include <math.h>
#include <stdlib.h>

int dirs[8][2] = {{2, -1}, {2, 1}, {1, -2}, {1, 2}, {-1, -2}, {-1, 2}, {-2, -1}, {-2, 1}};
int size;

int dfs(int k, int r, int c) {
    if (k == 0) return 1;
    int res = 0;
    for (int i = 0; i < 8; ++i) {
        int nr = r + dirs[i][0];
        int nc = c + dirs[i][1];
        if (nr >= 0 && nr < size && nc >= 0 && nc < size) res += dfs(k - 1, nr, nc);
    }
    // 可能会溢出
    return res;
}

double knightProbability(int n, int k, int row, int column) {
    size = n;
    return dfs(k, row, column) / (pow(8, k));
}