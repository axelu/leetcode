
// 951. Flip Equivalent Binary Trees
// https://leetcode.com/problems/flip-equivalent-binary-trees/





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

    // preorder traversal
    bool dfs(TreeNode* root1, TreeNode* root2) {
        /*
        if( root1 == nullptr ) cout << "root1 null ";
        else cout << "root1 " << root1->val << " ";
        if( root2 == nullptr ) cout << "root2 null" << endl;
        else cout << "root2 " << root2->val << endl;
        */

        if( root1 == nullptr && root2 == nullptr )
            return true;
        if( ( root1 != nullptr && root2 == nullptr ) ||
            ( root1 == nullptr && root2 != nullptr ) )
            return false;
        if( root1->val != root2->val )
            return false;

        // root1 drives the direction, root2 follows
        // we need to select which route to go in root2
        bool root2right = false;  // did we go right?
        // root1 left
        if( root1->left == nullptr ) {
            // is there a nullptr child in root2?
            if( root2->left != nullptr && root2->right != nullptr ) {
                return false;
            }
            if( root2->left != nullptr ) {
                root2right = true;
            }
        } else {
            if( root2->left == nullptr && root2->right == nullptr ) {
                return false;
            }
            if( root2->left == nullptr ) {
                // must be the right node in root2
                root2right = true;
                bool res = dfs(root1->left,root2->right);
                if( !res ) return false;
            } else if( root2->left->val == root1->left->val ) {
                bool res = dfs(root1->left,root2->left);
                if( !res ) return false;
            } else {
                // must be the right node in root2
                root2right = true;
                bool res = dfs(root1->left,root2->right);
                if( !res ) return false;
            }
        }
        // root1 right
        return root2right ? dfs(root1->right,root2->left) : dfs(root1->right,root2->right);

    }

public:
    bool flipEquiv(TreeNode* root1, TreeNode* root2) {
        return dfs(root1,root2);
    }
};
