#include <stdio.h>
#include <stdlib.h>

int t, m;
int** choice;
int* data;
int res;

int mmax(int a, int b) { return a > b ? a : b; }

// 返回最大的总价值
void func(int time_left, int total_val, int cur_idx, int pre_val) {
    // 加不了，这条路径终止了
    if (time_left < 0) {
        res = mmax(res, total_val);
        return;
    }
    // 延迟累加上一次的价值
    total_val += pre_val;
    // 没得选了，或者背包满了
    if (cur_idx == m || time_left == 0) {
        res = mmax(res, total_val);
        return;
    }

    // 选 choice[cur_idx]
    func(time_left - choice[cur_idx][0], total_val, cur_idx + 1, choice[cur_idx][1]);
    // 不选 choice[cur_idx]
    func(time_left, total_val, cur_idx + 1, 0);
}

int main() {
    res = 0;
    scanf("%d %d", &t, &m);
    choice = malloc(sizeof(*choice) * m);
    data = malloc(sizeof(*data) * m * 2);
    for (int i = 0; i < m; i++) choice[i] = data + i * 2;
    for (int i = 0; i < m; i++) scanf("%d %d", &choice[i][0], &choice[i][1]);

    func(t, 0, 0, 0);

    printf("%d", res);
}