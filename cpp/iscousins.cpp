
// 993. Cousins in a Binary Tree
// https://leetcode.com/problems/cousins-in-binary-tree/

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
    int X,Y;
    bool foundX, foundY;
    int depthX, depthY;
    TreeNode* parentX;
    TreeNode* parentY;

    void dfs(TreeNode* root, int depth, TreeNode* parent) {
        if( foundX && foundY ) return;
        if( root == nullptr ) return;

        if( root->val == X ) {
            foundX = true;
            depthX = depth;
            parentX = parent;
            return;
        }
        if( root->val == Y ) {
            foundY = true;
            depthY = depth;
            parentY = parent;
            return;
        }

        dfs(root->left,depth+1,root);
        dfs(root->right,depth+1,root);
    }
public:
    bool isCousins(TreeNode* root, int x, int y) {
        X = x;
        Y = y;
        foundX = false;
        foundY = false;

        dfs(root,0,nullptr);

        return foundX && foundY && depthX == depthY && parentX != parentY;
    }
};
