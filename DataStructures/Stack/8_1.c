#include <stdio.h>
#include <stdlib.h>

#define MAXN 100005
#define MMAX(a, b) ((a) > (b) ? (a) : (b))

// stk[i][0] 存储鱼的体积
// stk[i][1] 存储这条鱼吃掉其右边所有能吃的鱼所需要的轮数（步数）
int stk[MAXN][2];
int sz;

int main() {
    int n;
    scanf("%d", &n);
    int* arr = malloc(sizeof(int) * n);
    for (int i = 0; i < n; ++i) scanf("%d", &arr[i]);

    sz = 0;
    int res = 0;

    // 从右向左逆序遍历鱼群
    for (int i = n - 1; i >= 0; --i) {
        int cur = arr[i];  // 当前鱼的体积
        int round = 0;     // 当前鱼吃掉右侧阻碍它的鱼所需要的轮数

        // 当栈不为空，且当前鱼的体积大于栈顶鱼的体积时
        // 说明当前大鱼可以吃掉栈顶的小鱼
        while (sz > 0 && stk[sz - 1][0] < cur) {
            /*
               当前鱼要吃掉整个栈顶鱼的“势力范围”，需要的时间取决于：
               1. round + 1：当前鱼一条一条吃掉栈顶这些小鱼本身积累的轮数。
               2. stk[sz - 1][1]：
                  栈顶那条小鱼在被吃之前，它自己吃右边更小的鱼所花的时间。
                  因为它们是并行发生的，因此取两者的较大值。
             */
            round = MMAX(round + 1, stk[sz - 1][1]);
            res = MMAX(res, round);
            --sz;
        }

        stk[sz][0] = cur;
        stk[sz][1] = round;
        ++sz;
    }

    printf("%d\n", res);

    return 0;
}
