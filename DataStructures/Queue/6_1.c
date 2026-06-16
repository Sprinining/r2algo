#include <stdlib.h>

int cmp(const void* a, const void* b) { return *(int*)a - *(int*)b; }

// 检查在当前 mid 限制下，工人能否成功完成任务
int judge(int* tasks, int* workers, int pills, int strength, int tl, int tr,
          int wl, int wr, int tasksSize) {
    int* deque = malloc(sizeof(int) * tasksSize);
    int front = 0, rear = 0;
    int cost = 0;  // 记录吃药的总数
    int j = tl;    // 任务扫描指针

    // 工人从弱到强遍历
    for (int i = wl; i <= wr; ++i) {
        // 【步骤 1】不吃药能做的任务全部进队，rear 右移扩容
        while (j <= tr && tasks[j] <= workers[i]) {
            deque[rear++] = j++;
        }

        // l 代表窗口左端（小任务），r 代表窗口右端（大任务）
        int l = front;
        int r = rear - 1;

        // 【步骤 2】不吃药贪心：优先匹配并消耗核心窗口左端 l 的极小任务
        if (front < rear && tasks[deque[l]] <= workers[i]) {
            front++;  // 缩小左边界
        } else {
            // 【步骤 3】氪药扩窗：把吃药后能覆盖的任务继续塞入队列
            while (j <= tr && tasks[j] <= workers[i] + strength) {
                deque[rear++] = j++;
            }

            // 重新更新窗口右端指针 r
            r = rear - 1;

            // 核心窗口变空（无任务可用），直接宣告失败
            if (front == rear) {
                free(deque);
                return 0;
            }

            // 充分压榨药效：直接消灭当前核心窗口右端 r 的极大任务
            rear--;  // 缩小右边界
            cost++;
        }
    }

    return cost <= pills;
}

int maxTaskAssign(int* tasks, int tasksSize, int* workers, int workersSize,
                  int pills, int strength) {
    // 先给任务和工人进行升序排序
    qsort(tasks, tasksSize, sizeof(int), cmp);
    qsort(workers, workersSize, sizeof(int), cmp);

    int left = 0;
    int right = tasksSize < workersSize ? tasksSize : workersSize;

    // 标准二分搜索右边界
    while (left <= right) {
        int mid = left + ((right - left) >> 1);

        // 传入任务区间 [0, mid-1] 和最强工人区间进行判定
        if (judge(tasks, workers, pills, strength, 0, mid - 1,
                  workersSize - mid, workersSize - 1, tasksSize)) {
            left = mid + 1;  // 能完成，尝试挑战更多任务
        } else {
            right = mid - 1;  // 完成不了，减少任务量
        }
    }

    return right;
}
