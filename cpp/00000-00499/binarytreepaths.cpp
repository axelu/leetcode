
// 257. Binary Tree Paths
// https://leetcode.com/problems/binary-tree-paths/


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
    vector<string> ans;
    deque<int> path;

    void dfs(TreeNode* root) {
        path.push_back(root->val);

        if( root->left == nullptr && root->right == nullptr ) {
            // leaf node
            string s = to_string(path[0]);
            for(int i = 1; i < path.size(); ++i) {
                s += "->" + to_string(path[i]);
            }
            ans.push_back(s);
        }

        if( root->left != nullptr ) dfs(root->left);
        if( root->right != nullptr ) dfs(root->right);
        path.pop_back();
    }
public:
    vector<string> binaryTreePaths(TreeNode* root) {
        if( root == nullptr ) return ans;

        dfs(root);

        return ans;
    }
};
