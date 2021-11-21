
// 111. Minimum Depth of Binary Tree
// https://leetcode.com/problems/minimum-depth-of-binary-tree/


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
    int minDepth(TreeNode* root) {
        if ( root == nullptr ) return 0;
        if ( root->left == nullptr && root->right == nullptr ) return 1;

        int depth = 1;
        int mindepth = INT_MAX;
        explore(root, depth, mindepth);
        return mindepth;
    }
private:
    int explore(TreeNode* n, int depth, int& mindepth) {
        if ( n == nullptr ) {
            return 0;
        }

        int l = explore(n->left, depth+1, mindepth);
        int r = explore(n->right, depth+1, mindepth);

        if ( l + r == 0 )
            if (mindepth > depth ) mindepth = depth;

        return 1;
    }
};
