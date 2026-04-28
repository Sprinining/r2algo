// 在这棵普通树里，找出一整棵完整子树（必须连根带所有后代，不能切一半），满足：
// 这棵子树是合法 BST，在所有合法 BST 子树里，选节点数量最多的那一个
// 最终返回：这个最大 BST 子树的节点个数
// 左子树全部节点 < 根
// 右子树全部节点 > 根
// 左右子树各自也必须是 BST
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define MMAX(a, b) ((a) > (b) ? (a) : (b))
#define MMIN(a, b) ((a) > (b) ? (b) : (a))

typedef struct TreeNode {
    int val;
    struct TreeNode* left;
    struct TreeNode* right;
} TN;

typedef struct Info {
    int max;
    int min;
    int cnt;     // 结点总数
    bool isBST;  // 是否为 BST
} Info;

int res;

Info* dfs(TN* root) {
    if (root == NULL) return NULL;
    Info* node = malloc(sizeof(*node));
    node->max = root->val;
    node->min = root->val;
    node->cnt = 1;
    node->isBST = true;

    Info* l = dfs(root->left);
    if (l != NULL) {
        if (l->max >= root->val || !l->isBST) node->isBST = false;
        node->cnt += l->cnt;
        node->max = MMAX(node->max, l->max);
        node->min = MMIN(node->min, l->min);
    }

    Info* r = dfs(root->right);
    if (r != NULL) {
        if (r->min <= root->val || !r->isBST) node->isBST = false;
        node->cnt += r->cnt;
        node->max = MMAX(node->max, r->max);
        node->min = MMIN(node->min, r->min);
    }

    if (node->isBST) res = MMAX(res, node->cnt);
    return node;
}

int largestBSTSubtree(struct TreeNode* root) {
    res = 0;
    dfs(root);
    return res;
}

struct TreeNode* newNode(int val) {
    struct TreeNode* node = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    node->val = val;
    node->left = NULL;
    node->right = NULL;
    return node;
}

int main() {
    /**
     * 构造如下二叉树：
     *        10
     *       /  \
     *      5    15
     *     / \     \
     *    1   8     7
     *
     * 最大 BST 子树是：
     *      5
     *     / \
     *    1   8
     * 节点数 = 3
     */

    struct TreeNode* root = newNode(10);
    root->left = newNode(5);
    root->right = newNode(15);

    root->left->left = newNode(1);
    root->left->right = newNode(8);

    root->right->right = newNode(7);

    int result = largestBSTSubtree(root);

    printf("Largest BST Subtree Size: %d\n", result);

    return 0;
}
