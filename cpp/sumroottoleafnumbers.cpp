
// 129. Sum Root to Leaf Numbers
// https://leetcode.com/problems/sum-root-to-leaf-numbers/



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
    void dfs(TreeNode* root, string& path) {
        if( root == nullptr ) return;

        path += to_string(root->val);

        if( root->left == nullptr && root->right == nullptr )
            ans += stoi(path);

        dfs(root->left,path);
        dfs(root->right,path);

        // backtrack
        path.erase(path.size()-1);
    }

public:
    int sumNumbers(TreeNode* root) {
        ans = 0;
        string path = "";
        dfs(root,path);
        return ans;
    }
};
