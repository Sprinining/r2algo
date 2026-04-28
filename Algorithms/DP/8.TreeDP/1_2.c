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

Info dfs(TN* root) {
    // 哨兵
    if (root == NULL) return (Info){0x80000000, 0x7fffffff, 0, true};

    Info l = dfs(root->left);
    Info r = dfs(root->right);

    Info node;
    node.cnt = l.cnt + r.cnt + 1;
    node.max = MMAX(root->val, MMAX(l.max, r.max));
    node.min = MMIN(root->val, MMIN(l.min, r.min));

    if (l.isBST && r.isBST && l.max < root->val && r.min > root->val) {
        node.isBST = true;
        res = MMAX(res, node.cnt);
    } else {
        node.isBST = false;
    }
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
    // ==========================================
    // 测试用例1：你原来的树 → 预期输出 3
    // ==========================================
    printf("===== 测试用例 1 =====\n");
    struct TreeNode* root1 = newNode(10);
    root1->left = newNode(5);
    root1->right = newNode(15);
    root1->left->left = newNode(1);
    root1->left->right = newNode(8);
    root1->right->right = newNode(7);
    printf("Largest BST Subtree Size: %d\n\n", largestBSTSubtree(root1));

    // ==========================================
    // 测试用例2：整棵树都是 BST → 预期输出 6
    // ==========================================
    printf("===== 测试用例 2 =====\n");
    struct TreeNode* root2 = newNode(4);
    root2->left = newNode(2);
    root2->right = newNode(6);
    root2->left->left = newNode(1);
    root2->left->right = newNode(3);
    root2->right->right = newNode(7);
    printf("Largest BST Subtree Size: %d\n\n", largestBSTSubtree(root2));

    // ==========================================
    // 测试用例3：只有单个节点 → 预期输出 1
    // ==========================================
    printf("===== 测试用例 3 =====\n");
    struct TreeNode* root3 = newNode(1);
    printf("Largest BST Subtree Size: %d\n\n", largestBSTSubtree(root3));

    return 0;
}
