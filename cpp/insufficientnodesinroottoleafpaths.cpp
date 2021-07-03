
// 1080. Insufficient Nodes in Root to Leaf Paths
// https://leetcode.com/problems/insufficient-nodes-in-root-to-leaf-paths/




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
    TreeNode* dfs(TreeNode* root, int limit, int pathSum) {

        if( root->left == nullptr & root->right == nullptr ) {
            // leave node
            return pathSum+root->val >= limit ? root : nullptr;
        }

        if( root->left != nullptr )
            root->left  = dfs(root->left, limit,pathSum+root->val);
        if( root->right != nullptr )
            root->right = dfs(root->right,limit,pathSum+root->val);

        if( root->left == nullptr & root->right == nullptr ) {
            // our node is now a leave node
            // return pathSum+root->val >= limit ? root : nullptr;
            return nullptr;
        } else {
            return root;
        }
    }

public:
    TreeNode* sufficientSubset(TreeNode* root, int limit) {
        return dfs(root,limit,0);
    }
};
