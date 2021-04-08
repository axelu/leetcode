
// 988. Smallest String Starting From Leaf
// https://leetcode.com/problems/smallest-string-starting-from-leaf/




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
    string ans;

    void dfs(TreeNode* root, string& path) {
        path.insert(path.begin(),root->val+'a');
        if( root->left == nullptr && root->right == nullptr )
            if( path < ans ) ans = path;

        if( root->left != nullptr )
            dfs(root->left,path);
        if( root->right != nullptr )
            dfs(root->right,path);

        // backtrack
        path.erase(0,1);
    }
public:
    string smallestFromLeaf(TreeNode* root) {
        if( root == nullptr ) return "";
        ans = string(8500,'z'); // initialize to max
        string path = "";
        dfs(root,path);
        return ans;
    }
};
