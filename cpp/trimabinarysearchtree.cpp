
// 669. Trim a Binary Search Tree
// https://leetcode.com/problems/trim-a-binary-search-tree/
// day 2 February 2021 challenge
// https://leetcode.com/explore/featured/card/february-leetcoding-challenge-2021/584/week-1-february-1st-february-7th/3626/



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
    TreeNode* Root;

    void trimLow(TreeNode* root, int low, TreeNode* parent) {
        if( root == nullptr ) return;

        if( root->val > low ) {
            trimLow(root->left,low,root);
        } else if( root->val < low ) {
            if( parent != nullptr ) {
                if( parent->left != nullptr && parent->left == root ) {
                    parent->left = root->right;
                } else {
                    parent->right = root->right;
                }
            } else {
                Root = root->right;
            }
            trimLow(root->right,low,parent);
        } else {
            root->left = nullptr;
        }
    }

    void trimHigh(TreeNode* root, int high, TreeNode* parent) {
        if( root == nullptr ) return;

        if( root->val < high ) {
            trimHigh(root->right,high,root);
        } else if( root->val > high ) {
            if( parent != nullptr ) {
                if( parent->left != nullptr && parent->left == root ) {
                    parent->left = root->left;
                } else {
                    parent->right = root->left;
                }
            } else {
                Root = root->left;
            }
            trimHigh(root->left,high,parent);
        } else {
            root->right = nullptr;
        }
    }
public:
    TreeNode* trimBST(TreeNode* root, int low, int high) {
        Root = root;
        trimLow(root,low,nullptr);
        trimHigh(Root,high,nullptr);
        return Root;
    }
};
