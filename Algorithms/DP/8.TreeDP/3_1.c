#define MMAX(a, b) ((a) > (b) ? (a) : (b))

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

int res;

int dfs(struct TreeNode *root) {
    if (root == NULL) return 0;
    int l = dfs(root->left);
    int r = dfs(root->right);
    res = MMAX(res, l + r);
    return MMAX(l, r) + 1;
}
int diameterOfBinaryTree(struct TreeNode *root) {
    res = 0;
    dfs(root);
    return res;
}
