struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

// 全局摄像头数量
int res;

// 0: 未覆盖
// 1: 已覆盖，但没有摄像头
// 2: 有摄像头
int dfs(struct TreeNode *root) {
    if (root == NULL) return 1;

    int l = dfs(root->left);
    int r = dfs(root->right);

    // 子节点有未覆盖，当前必须放摄像头
    if (l == 0 || r == 0) {
        ++res;
        return 2;
    }

    // 子节点都被覆盖，但都没有摄像头，当前未覆盖（等父节点处理）
    if (l == 1 && r == 1) return 0;

    // 子节点都被覆盖，且至少有一个摄像头，当前被覆盖
    return 1;
}

int minCameraCover(struct TreeNode *root) {
    res = 0;
    if (dfs(root) == 0) ++res;
    return res;
}
