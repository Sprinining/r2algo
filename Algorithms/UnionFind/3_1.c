#include <stdbool.h>
#include <string.h>

#define MAXN 300

int father[MAXN];
int rank[MAXN];
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

bool isSimilar(char* a, char* b) {
    int len = strlen(a);
    int diff = 0;
    for (int i = 0; i < len; ++i) {
        if (a[i] != b[i]) ++diff;
    }
    return diff == 0 || diff == 2;
}

int numSimilarGroups(char** strs, int strsSize) {
    build(strsSize);
    for (int i = 0; i < strsSize; ++i)
        for (int j = i + 1; j < strsSize; ++j)
            if (isSimilar(strs[i], strs[j])) unite(i, j);
    return sets;
}
