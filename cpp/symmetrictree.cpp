
// Symmetric Tree
//

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
public:
    bool isSymmetric(TreeNode* root) {
        // early exits
        if ( root == nullptr ) return true;
        if ( root->left == nullptr && root->right == nullptr ) return true;
        if ( root->left == nullptr && root->right != nullptr ) return false;
        if ( root->left != nullptr && root->right == nullptr ) return false;

        return isSymmetric(root->left, root->right);
    }

    bool isSymmetric(TreeNode* t1, TreeNode* t2) {
        if ( t1 == nullptr && t2 == nullptr ) return true;
        if ( t1 == nullptr && t2 != nullptr ) return false;
        if ( t1 != nullptr && t2 == nullptr ) return false;
        if ( t1->val != t2->val ) return false;

        return ( isSymmetric(t1->left, t2->right) && isSymmetric(t1->right, t2->left) ) ? true : false;
        }
};
