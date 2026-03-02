#include <stdio.h>
#include <stdlib.h>

int t, m;
int** choice;
int* data;

int mmax(int a, int b) { return a > b ? a : b; }

// 带返回值
// 返回最大的总价值
int func(int time_left, int cur_idx) {
    // 没得选或者背包满了
    if (cur_idx == m || time_left == 0) return 0;

    // 不选 choice[cur_idx]
    int p1 = func(time_left, cur_idx + 1);
    // 选 choice[cur_idx]，前提不超过背包容量
    int p2 = 0;
    if (time_left >= choice[cur_idx][0])
        p2 = func(time_left - choice[cur_idx][0], cur_idx + 1) + choice[cur_idx][1];
    return mmax(p1, p2);
}

int main() {
    scanf("%d %d", &t, &m);
    choice = malloc(sizeof(*choice) * m);
    data = malloc(sizeof(*data) * m * 2);
    for (int i = 0; i < m; i++) choice[i] = data + i * 2;
    for (int i = 0; i < m; i++) scanf("%d %d", &choice[i][0], &choice[i][1]);

    printf("%d", func(t, 0));
}