
// 1430. Check If a String Is a Valid Sequence from Root to Leaves Path in a Binary Tree
// https://leetcode.com/problems/check-if-a-string-is-a-valid-sequence-from-root-to-leaves-path-in-a-binary-tree/



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
    bool ans;
    void dfs(TreeNode* root, vector<int>& arr, int n, int pos) {
        if( nullptr == root || ans )
            return;

        if( root->val != arr[pos] )
            return;

        if( pos == n-1 ) {
            if( nullptr == root->left && nullptr == root->right )
                ans = true;
            return;
        }

        dfs(root->left,arr,n,pos+1);
        dfs(root->right,arr,n,pos+1);
    }


public:
    bool isValidSequence(TreeNode* root, vector<int>& arr) {
        ans = false;
        dfs(root,arr,arr.size(),0);
        return ans;
    }
};
