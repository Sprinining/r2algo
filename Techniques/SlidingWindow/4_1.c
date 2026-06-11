#include <stdbool.h>
#include <stdlib.h>

bool func(int* rest, int n, int start) {
    int oil = 0;
    int cur = start;
    for (int i = 0; i < n; ++i) {
        oil += rest[cur];
        if (oil < 0) return false;
        cur = (cur + 1) % n;
    }
    return true;
}

int canCompleteCircuit(int* gas, int gasSize, int* cost, int costSize) {
    int n = gasSize;
    int* rest = malloc(sizeof(int) * n);

    for (int i = 0; i < n; ++i) rest[i] = gas[i] - cost[i];

    for (int i = 0; i < n; ++i)
        if (func(rest, n, i)) return i;
    return -1;
}
