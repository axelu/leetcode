
// 1302. Deepest Leaves Sum
// https://leetcode.com/problems/deepest-leaves-sum/


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
    int mxDepth;
    int ans;
    void dfs1(TreeNode* root, int depth) {
        if( root == nullptr ) return;
        if( depth > mxDepth ) mxDepth = depth;
        dfs1(root->left,depth+1);
        dfs1(root->right,depth+1);
    }
    void dfs2(TreeNode* root, int depth) {
        if( root == nullptr ) return;
        if( depth == mxDepth ) {
            // must be a leave
            ans += root->val;
        }
        dfs2(root->left,depth+1);
        dfs2(root->right,depth+1);
    }

public:
    int deepestLeavesSum(TreeNode* root) {
        mxDepth = 0;
        dfs1(root,0);
        ans = 0;
        dfs2(root,0);
        return ans;
    }
};
