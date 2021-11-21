
// 1973. Count Nodes Equal to Sum of Descendants
// https://leetcode.com/problems/count-nodes-equal-to-sum-of-descendants/





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

    long postorder(TreeNode* root, int& ans) {

        long lft = 0;
        if( root->left != nullptr )
            lft = postorder(root->left,ans);
        long rgt = 0;
        if( root->right != nullptr )
            rgt = postorder(root->right,ans);

        if( root->val == lft+rgt )
            ++ans;

        return (long)root->val+lft+rgt;
    }


public:
    int equalToDescendants(TreeNode* root) {

        int ans = 0;
        postorder(root,ans);
        return ans;
    }
};
