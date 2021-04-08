
// Path Sum
// https://leetcode.com/problems/path-sum/



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
    bool hasPathSum(TreeNode* root, int sum) {
        if ( root == nullptr ) return false;

        bool match = false;
        explore(root, 0, sum, match);
        return match;
    }
private:
    int explore(TreeNode* n, int cs, const int& sum, bool& match) {
        if ( match ) return 1;
        if ( n == nullptr ) return 0;

        int l = explore(n->left, cs + n->val, sum, match);
        int r = explore(n->right, cs + n->val, sum, match);

        if ( l + r == 0 ) {
            // i am a leaf node
            if ( cs + n->val == sum ) match = true;
        }

        return 1;
    }
};
