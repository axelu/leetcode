
// 776. Split BST
// https://leetcode.com/problems/split-bst/




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
    TreeNode* L; // root of tree with all nodes smaller or equal to the target
    TreeNode* R; // root of tree with all nodes greater than the target
    TreeNode* l;

    void rec(TreeNode* root, TreeNode* parent, int V) {
        if( root == nullptr ) return;

        if( root->val <= V ) {
            TreeNode* rc = root->right; // right child
            if( parent != nullptr ) {
                // is root the right or left child of the parent?
                // our right node will replace us on the parent
                if( parent->left == root ) {
                    parent->left = rc;
                } else {
                    parent->right = rc;
                }
            } else {
                R = rc;
            }
            if( l == nullptr ) {
                L = root;
                l = root;
            } else {
                l->right = root;
                l = root;
            }
            root->right = nullptr;
            if( root->val == V ) return; // we are done
            rec(rc,parent,V);            // continue to the right
        } else {
            // root->val > V
            if( R == nullptr ) R = root;
            // continue to the left
            rec(root->left,root,V);
        }
    }


public:
    vector<TreeNode*> splitBST(TreeNode* root, int V) {
        L = nullptr; l = nullptr;
        R = nullptr;

        // base cases
        if( root == nullptr ) return {L,R};
        if( root->val == V ) {
            R = root->right;
            root->right = nullptr;
            return {root,R};
        }

        rec(root,nullptr,V);
        return {L,R};
    }
};
