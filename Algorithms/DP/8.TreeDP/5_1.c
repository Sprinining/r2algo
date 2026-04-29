#define MMAX(a, b) ((a) > (b) ? (a) : (b))

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

typedef struct Info {
    // 当前结点偷
    int steal;
    // 当前结点不偷
    int nosteal;
} Info;

Info dfs(struct TreeNode *root) {
    if (root == NULL) return (Info){0, 0};
    Info l = dfs(root->left);
    Info r = dfs(root->right);
    Info node;
    // 当前位置偷，那么左右孩子不能偷
    node.steal = root->val + l.nosteal + r.nosteal;
    // 当前位置不偷，左右孩子可偷可不偷
    node.nosteal = MMAX(l.steal, l.nosteal) + MMAX(r.steal, r.nosteal);
    return node;
}

int rob(struct TreeNode *root) {
    Info info = dfs(root);
    return MMAX(info.steal, info.nosteal);
}
