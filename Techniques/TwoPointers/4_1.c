#include <stdlib.h>

int cmp(const void* a, const void* b) {
    int x = *(int*)a;
    int y = *(int*)b;
    if (x > y) return 1;
    if (x < y) return -1;
    return 0;
}

int numRescueBoats(int* people, int peopleSize, int limit) {
    // 按体重从轻到重排序
    qsort(people, peopleSize, sizeof(people[0]), cmp);

    int res = 0;
    int l = 0, r = peopleSize - 1;

    while (l <= r) {
        int sum = (l == r) ? people[l] : people[l] + people[r];
        if (sum <= limit) ++l;
        --r;
        ++res;
    }

    return res;
}
