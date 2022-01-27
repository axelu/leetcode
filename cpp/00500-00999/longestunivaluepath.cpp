
// 687. Longest Univalue Path
// https://leetcode.com/problems/longest-univalue-path/




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
    int ans;

    // postorder traversal
    int dfs(TreeNode* root) {
        // returns the length of the longest path where each node in the path has the same value

        if( root == nullptr ) return 0;

        int l = dfs(root->left);
        int r = dfs(root->right);

        if( root->left != nullptr && root->left->val == root->val )
            l += 1;
        else
            l = 0;

        if( root->right != nullptr && root->right->val == root->val )
            r += 1;
        else
            r = 0;

        int t = 0;
        if( root->left != nullptr && root->right != nullptr ) {
            if( root->left->val == root->val && root->right->val == root->val ) {
                // there is a path through this node
                t = l + r;
            }
        }

        ans = max({ans,l,r,t});
        return max(l,r);
    }
public:
    int longestUnivaluePath(TreeNode* root) {
        ans = 0;
        dfs(root);
        return ans;
    }
};
