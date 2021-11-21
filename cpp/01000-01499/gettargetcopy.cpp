
// 1379. Find a Corresponding Node of a Binary Tree in a Clone of That Tree
// https://leetcode.com/problems/find-a-corresponding-node-of-a-binary-tree-in-a-clone-of-that-tree/
// day 2 January 2020 challenge
// https://leetcode.com/explore/featured/card/january-leetcoding-challenge-2021/579/week-1-january-1st-january-7th/3590/ 

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

class Solution {
private:
    bool found;
    TreeNode* Target;
    TreeNode* ans;

    void dfs(TreeNode* root) {
        if( root == nullptr ) return;
        if( found ) return;
        if( root->val == Target->val ) {
            found = true;
            ans = root;
            return;
        }
        dfs(root->left);  // left
        dfs(root->right); // right
    }
public:
    TreeNode* getTargetCopy(TreeNode* original, TreeNode* cloned, TreeNode* target) {
        // constraint: The values of the nodes of the tree are unique.
        // hence we should be able to simply locate the node in the cloned tree with
        // cloned->val == target->val.

        found = false;
        Target = target;
        dfs(cloned);
        return ans;
    }
};
