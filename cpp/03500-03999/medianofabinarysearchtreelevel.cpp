
// 3831. Median of a Binary Search Tree Level
// https://leetcode.com/problems/median-of-a-binary-search-tree-level/


/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
private:
    vector<int> nodes; // nodes on level 'level'

    void dfs(TreeNode* root, int cur_level, int max_level) {
        if( root == nullptr )
            return;

        if( cur_level == max_level ) {
            nodes.push_back(root->val);
            return;
        }

        dfs(root->left, cur_level + 1, max_level);
        dfs(root->right, cur_level + 1, max_level);
        return;
    }

public:
    int levelMedian(TreeNode* root, int level) {
        dfs(root, 0, level);
        int nodes_sz = nodes.size();
        if( nodes_sz == 0 )
            return -1;

        sort(begin(nodes), end(nodes));
        int m = nodes.size()/2;
        return nodes[m];
    }
};
