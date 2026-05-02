#include <stdlib.h>

// 下标最多 100000，除此以外多给一个位置给右侧哨兵
#define MAX_N 100002
#define MMAX(a, b) ((a) > (b) ? (a) : (b))

struct TreeNode {
    int val;
    struct TreeNode* left;
    struct TreeNode* right;
};

// 结点总数
int cnt;
// dfn 序号，从 1 开始，结点值也是从 1 开始
int dfn[MAX_N];
// 树的结点个数
int sz[MAX_N];
// 根节点到当前结点经过的边数，下标为 dfn 序号
int depth[MAX_N];
// lmax[i] = depth[1, i] 上的最大值
int lmax[MAX_N];
int rmax[MAX_N];

void dfs(struct TreeNode* root, int deep) {
    if (root == NULL) return;
    int u = root->val;
    int idx = ++cnt;
    // 记录 dfn 序号
    dfn[u] = idx;
    // 初始化子树大小
    sz[u] = 1;
    // 更新路径长
    depth[idx] = deep;

    if (root->left != NULL) {
        dfs(root->left, deep + 1);
        sz[u] += sz[root->left->val];
    }

    if (root->right != NULL) {
        dfs(root->right, deep + 1);
        sz[u] += sz[root->right->val];
    }
}

int* treeQueries(struct TreeNode* root, int* queries, int queriesSize, int* returnSize) {
    *returnSize = queriesSize;
    int* res = calloc(queriesSize, sizeof(*res));
    cnt = 0;
    dfs(root, 0);

    // 两端哨兵
    lmax[0] = 0;
    for (int i = 1; i <= cnt; ++i) lmax[i] = MMAX(lmax[i - 1], depth[i]);
    rmax[cnt + 1] = 0;
    for (int i = cnt; i >= 1; --i) rmax[i] = MMAX(rmax[i + 1], depth[i]);

    for (int i = 0; i < queriesSize; ++i) {
        // 子树根节点值
        int u = queries[i];
        // 子树 dfn 序号范围
        int l = dfn[u];
        int r = l + sz[u] - 1;
        // depth 上 [l, r] 范围外的最大值
        res[i] = MMAX(lmax[l - 1], rmax[r + 1]);
    }
    return res;
}
