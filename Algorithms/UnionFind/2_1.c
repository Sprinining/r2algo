#define MAXN 30

// 下标为情侣组号，组号为情侣编号/2
int father[MAXN];
// 记录集合元素个数
int sz[MAXN];
int sets;

void build(int n) {
    for (int i = 0; i < n; ++i) {
        father[i] = i;
        sz[i] = 1;
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
    if (sz[fa] > sz[fb]) {
        father[fb] = fa;
        sz[fa] += sz[fb];
    } else {
        father[fa] = fb;
        sz[fb] += sz[fa];
    }
    // 集合总数减一
    --sets;
}

int minSwapsCouples(int* row, int rowSize) {
    int n = rowSize / 2;
    build(n);
    // 所在的情侣组合并
    for (int i = 0; i < rowSize; i += 2) unite(row[i] / 2, row[i + 1] / 2);
    // 每个情侣组集合有 a 组，则这个集合至少需要 a - 1 次交换
    // 一共有 n 个情侣组（每组两个人），总的交换次数就是 n - 集合总数
    return n - sets;
}
