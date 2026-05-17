#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   public:
    // 记录第一次遇到的石头的编号，以行列为 key，石头编号为 value
    unordered_map<int, int> rowFirst;
    unordered_map<int, int> colFirst;
    vector<int> father;
    int sets;

    void build(int n) {
        rowFirst.clear();
        colFirst.clear();
        father.resize(n);
        for (int i = 0; i < n; ++i) father[i] = i;
        sets = n;
    }

    int find(int x) {
        if (x == father[x]) return x;
        return father[x] = find(father[x]);
    }

    void unite(int a, int b) {
        int fa = find(a);
        int fb = find(b);
        if (fa == fb) return;
        father[fa] = fb;
        --sets;
    }

    // 每块石头是一个节点。如果两块石头同行或同列，就连一条边。
    // 最终形成的集合，就是一张图，节点 = 石头，边 = 同行/同列关系。
    // 换句话说，每个连通块是一个图的连通分量。
    // 规则保证每个连通分量最后只会剩一个石头
    int removeStones(vector<vector<int>>& stones) {
        int n = stones.size();
        build(n);

        for (int i = 0; i < n; ++i) {
            int row = stones[i][0];
            int col = stones[i][1];
            // 所有在行列上有关联的都合并到一起
            if (rowFirst.find(row) == rowFirst.end()) {
                // 该行第一次出现
                rowFirst[row] = i;
            } else {
                // 和之前在这行上第一次出现的石头合并到一个集合
                unite(i, rowFirst[row]);
            }
            if (colFirst.find(col) == colFirst.end()) {
                // 该行第一次出现
                colFirst[col] = i;
            } else {
                // 和之前在这行上第一次出现的石头合并到一个集合
                unite(i, colFirst[col]);
            }
        }
        // 最少剩 sets 个石头，最多移除 len - sets 个石头
        return n - sets;
    }
};
