
// 113. Path Sum II
// https://leetcode.com/problems/path-sum-ii/



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
    void dfs(TreeNode* root, int& sum, vector<int>& path, int& targetSum, vector<vector<int>>& ans) {
        int val = root->val;

        path.push_back(val);
        sum += val;



        if( root->left == nullptr && root->right == nullptr ) {
            // leaf
            if( sum == targetSum )
                ans.push_back(path);
        }

        // left
        if( root->left != nullptr )
            dfs(root->left,sum,path,targetSum,ans);
        // right
        if( root->right != nullptr )
            dfs(root->right,sum,path,targetSum,ans);


        // backtrack
        path.pop_back();
        sum -= val;
    }

public:
    vector<vector<int>> pathSum(TreeNode* root, int targetSum) {
        vector<vector<int>> ans;
        if( root == nullptr )
            return ans;

        int sum = 0;
        vector<int> path;
        dfs(root,sum,path,targetSum,ans);
        return ans;
    }
};
