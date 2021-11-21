
// 104. Maximum Depth of Binary Tree
// https://leetcode.com/problems/maximum-depth-of-binary-tree/

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
public:
    int maxDepth(TreeNode* root) {

        if ( root == nullptr ) return 0;
        if ( root->left == nullptr && root->right == nullptr ) return 1;

        depth = 0;
        explore(root, depth);
        return depth;
    }
private:
    int depth;
    void explore(TreeNode* root, int y) {

        if (root == nullptr) return;
        y +=1;
        if ( y > depth ) depth = y;
        explore(root->left,y);
        explore(root->right,y);

    }
};
