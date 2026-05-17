#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 100000

int cmp(const void* a, const void* b) {
    int* arr1 = *((int**)a);
    int* arr2 = *((int**)b);
    if (arr1[2] > arr2[2]) {
        return 1;
    } else if (arr1[2] < arr2[2]) {
        return -1;
    }
    return 0;
}

int father[MAXN];
// 集合是否知道秘密
bool knew[MAXN];

void build(int n, int first) {
    memset(knew, 0, sizeof(knew));
    for (int i = 0; i < n; ++i) father[i] = i;
    father[first] = 0;
    knew[0] = true;
}

int find(int x) {
    if (father[x] == x) return x;
    return father[x] = find(father[x]);
}

void unite(int a, int b) {
    int fa = find(a);
    int fb = find(b);
    if (fa == fb) return;
    father[fb] = fa;
    knew[fa] |= knew[fb];
}

int* findAllPeople(int n, int** meetings, int meetingsSize,
                   int* meetingsColSize, int firstPerson, int* returnSize) {
    // 根据会议时间升序排序
    qsort(meetings, meetingsSize, sizeof(*meetings), cmp);
    build(n, firstPerson);

    int m = meetingsSize;
    for (int l = 0, r; l < m; l = r + 1) {
        r = l;
        while (r + 1 < m && meetings[r][2] == meetings[r + 1][2]) ++r;

        // [l, r]
        // 范围是同一时间，这些专家最终合并成多个集合，其中可能有的集合会知道秘密
        for (int i = l; i <= r; ++i) unite(meetings[i][0], meetings[i][1]);

        for (int i = l; i <= r; ++i) {
            int a = meetings[i][0];
            int b = meetings[i][1];
            // 不知道秘密的集合全都拆散，里面的专家全都各自成为一个集合
            // 之后的时间点他们又不一定在同一个集合，所以要拆散防止干扰后面判断
            if (!knew[find(a)]) {
                father[a] = a;
                father[b] = b;
            }
            // 已经知道秘密的集合保留，可以把秘密在后面的时间点告诉别人
        }
    }

    int* res = malloc(sizeof(*res) * n);
    int len = 0;
    for (int i = 0; i < n; ++i) {
        if (!knew[find(i)]) continue;
        res[len++] = i;
    }
    *returnSize = len;
    return res;
}
