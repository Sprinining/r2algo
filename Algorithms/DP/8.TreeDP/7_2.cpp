#include <iostream>
#include <unordered_map>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *l, TreeNode *r) : val(x), left(l), right(r) {}
};

class Solution {
   public:
    int result = 0;

    int pathSum(TreeNode *root, int targetSum) {
        // key: 前缀和，value: 该前缀和出现的次数
        unordered_map<long long, int> prefixCount;

        // 前缀和为 0 出现 1 次
        prefixCount[0] = 1;

        dfs(root, 0, targetSum, prefixCount);
        return result;
    }

   private:
    void dfs(TreeNode *node, long long currentSum, int target, unordered_map<long long, int> &prefixCount) {
        if (!node) return;

        // 更新当前路径的前缀和
        currentSum += node->val;

        // 如果存在某个前缀和 = currentSum - target
        // 那说明从那个节点之后到当前节点的路径和 = target
        if (prefixCount.count(currentSum - target)) result += prefixCount[currentSum - target];

        // 记录当前前缀和
        ++prefixCount[currentSum];

        // 递归左右子树
        dfs(node->left, currentSum, target, prefixCount);
        dfs(node->right, currentSum, target, prefixCount);

        // 回溯：当前节点处理完后，要把它的前缀和撤销
        // 否则会影响兄弟节点（路径不再是同一条）
        --prefixCount[currentSum];
    }
};
