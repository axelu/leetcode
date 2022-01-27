
// 513. Find Bottom Left Tree Value
// https://leetcode.com/problems/find-bottom-left-tree-value/


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
    int findBottomLeftValue(TreeNode* root) {

        // BFS
        queue<pair<TreeNode*,int>> q;
        pair<TreeNode*,int> qe;
        q.push({root,0});
        int currDepth = -1;
        int ans;
        while( !q.empty() ) {
            qe = q.front();
            q.pop();
            if( qe.second != currDepth ) {
                ans = qe.first->val;
                currDepth = qe.second;
            }
            if( qe.first->left != nullptr ) q.push({qe.first->left,qe.second+1});
            if( qe.first->right != nullptr ) q.push({qe.first->right,qe.second+1});
        }
        return ans;
    }
};
