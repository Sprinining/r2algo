#include <stdlib.h>

#define MMAX(a, b) ((a) > (b) ? (a) : (b))
#define MMIN(a, b) ((a) > (b) ? (b) : (a))

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

typedef struct Info {
    int sum;
    int max;
    int min;
    bool isBST;
} Info;

int res;

Info dfs(struct TreeNode *root) {
    if (root == NULL) return (Info){0, 0x80000000, 0x7fffffff, true};
    Info l = dfs(root->left);
    Info r = dfs(root->right);
    Info node;
    node.sum = root->val + l.sum + r.sum;
    node.max = MMAX(root->val, MMAX(l.max, r.max));
    node.min = MMIN(root->val, MMIN(l.min, r.min));
    if (l.isBST && r.isBST && l.max < root->val && root->val < r.min) {
        node.isBST = true;
        res = MMAX(res, node.sum);
    } else {
        node.isBST = false;
    }
    return node;
}

int maxSumBST(struct TreeNode *root) {
    res = 0;
    dfs(root);
    return res;
}
