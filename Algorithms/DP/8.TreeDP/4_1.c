#include <math.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

typedef struct Info {
    int cnt;
    int coins;
    int move;
} Info;

Info dfs(struct TreeNode *root) {
    if (root == NULL) return (Info){0, 0, 0};
    Info l = dfs(root->left);
    Info r = dfs(root->right);
    Info node;
    node.cnt = l.cnt + r.cnt + 1;
    node.coins = l.coins + r.coins + root->val;
    // 左、右子树已经全部分配完成（每个节点 1 个硬币）
    // 所有多余或缺少的硬币，全部集中到了当前子树的根节点
    // abs(l.cnt - l.coins)：左子树与当前节点之间的硬币交接步数
    // abs(r.cnt - r.coins)：右子树与当前节点之间的硬币交接步数
    node.move = l.move + r.move + abs(l.cnt - l.coins) + abs(r.cnt - r.coins);
    return node;
}

int distributeCoins(struct TreeNode *root) {
    Info info = dfs(root);
    return info.move;
}
