
// 270. Closest Binary Search Tree Value
// https://leetcode.com/problems/closest-binary-search-tree-value/



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
    double diff;

    void search(TreeNode* root, double& target) {
        if( nullptr == root ) return;

        // calc diff to current node
        double t = abs(root->val - target);
        if( abs(t) < diff ) {
            diff = abs(t);
            ans = root->val;
        }

        if( abs(t) < 1e-9 ) {
            // root->val == target
            return;
        } else if( root->val > target ) {
            search(root->left,target);
        } else {
            search(root->right,target);
        }
    }
public:
    int closestValue(TreeNode* root, double& target) {
        ans = root->val;
        diff = abs(root->val-target);
        search(root,target);
        return ans;
    }
};
