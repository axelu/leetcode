
// 366. Find Leaves in a Binary Tree
// https://leetcode.com/problems/find-leaves-of-binary-tree/




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
    int dfs(TreeNode* root, vector<vector<int>>& ans) {
        if( nullptr == root ) return -1;

        int l = dfs(root->left,ans);
        int r = dfs(root->right,ans);

        int ansIdx = max(l,r) + 1;
        int n = ans.size();
        if( n == ansIdx )
            ans.push_back({root->val});
        else
            ans[ansIdx].push_back(root->val);

        return ansIdx;
    }
public:
    vector<vector<int>> findLeaves(TreeNode* root) {
        vector<vector<int>> ans;
        if( nullptr == root ) return ans;
        dfs(root,ans);
        return ans;
    }
};
