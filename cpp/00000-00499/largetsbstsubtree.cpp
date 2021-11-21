
// 333. Largest BST Subtree
// https://leetcode.com/problems/largest-bst-subtree/





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

    struct R {
        int mx;
        int mn;
        bool isValidBSTSubtree;
        int n;
    };

    R dfs(TreeNode* root) {
        R ret;

        // left
        bool isLeftSubtreeValid = true;
        int mn = root->val;
        int l = 0;
        if( root->left != nullptr ) {
            ret = dfs(root->left);
            if( ret.mx >= root->val || !ret.isValidBSTSubtree ) {
                isLeftSubtreeValid = false;
            }
            mn = ret.mn;
            l = ret.n;
        }

        // right
        bool isRightSubtreeValid = true;
        int mx = root->val;
        int r = 0;
        if( root->right != nullptr ) {
            ret = dfs(root->right);
            if( ret.mn <= root->val || !ret.isValidBSTSubtree ) {
                isRightSubtreeValid = false;
            }
            mx = ret.mx;
            r = ret.n;
        }

        int n = l+r+1;
        if( isLeftSubtreeValid && isRightSubtreeValid ) {
            ans = max(ans,n);
            return {mx,mn,true,n};
        }
        return {mx,mn,false,n};
    }

public:
    int largestBSTSubtree(TreeNode* root) {
        ans = 0;
        if( root == nullptr ) return ans;
        dfs(root);
        return ans;
    }
};
