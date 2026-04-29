struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

int target;

// 以当前节点为起始节点的路径
int startFromNow(struct TreeNode *root, long long sum) {
    if (root == NULL) return 0;
    sum += root->val;
    int cnt = 0;
    if (sum == target) ++cnt;
    cnt += startFromNow(root->left, sum) + startFromNow(root->right, sum);
    return cnt;
}

// 遍历整棵树，从每个节点开始尝试
int dfs(struct TreeNode *root) {
    if (root == NULL) return 0;
    return startFromNow(root, 0) + dfs(root->left) + dfs(root->right);
}

// 树长得像链表情况最坏，时间复杂度O(n^2)，
// 平衡树，时间复杂度为O(nlogn)
int pathSum(struct TreeNode *root, int targetSum) {
    target = targetSum;
    return dfs(root);
}
