#include <stdlib.h>

int dirs[8][2] = {{2, -1}, {2, 1}, {1, -2}, {1, 2}, {-1, -2}, {-1, 2}, {-2, -1}, {-2, 1}};
double** cur;
double* data1;
double** pre;
double* data2;

void swap(double*** a, double*** b) {
    double** c = *a;
    *a = *b;
    *b = c;
}

double knightProbability(int n, int k, int row, int column) {
    int layers = k + 1;
    int rows = n;
    int cols = n;
    cur = malloc(sizeof(*cur) * rows);
    pre = malloc(sizeof(*pre) * rows);
    data1 = malloc(sizeof(*data1) * rows * cols);
    data2 = malloc(sizeof(*data2) * rows * cols);
    for (int i = 0; i < rows; ++i) {
        cur[i] = data1 + i * cols;
        pre[i] = data2 + i * cols;
        for (int j = 0; j < cols; ++j) {
            pre[i][j] = 1.0;
        }
    }

    for (int i = 1; i < layers; ++i) {
        for (int r = rows - 1; r >= 0; --r) {
            for (int c = cols - 1; c >= 0; --c) {
                cur[r][c] = 0.0;
                for (int index = 0; index < 8; ++index) {
                    int br = r - dirs[index][0];
                    int bc = c - dirs[index][1];
                    if (br >= 0 && br < rows && bc >= 0 && bc < cols) cur[r][c] += pre[br][bc];
                }
                cur[r][c] /= 8.0;
            }
        }
        swap(&cur, &pre);
    }

    return pre[row][column];
}