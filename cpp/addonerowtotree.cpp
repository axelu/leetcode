
// 623. Add One Row to Tree
// https://leetcode.com/problems/add-one-row-to-tree/



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
    TreeNode* addOneRow(TreeNode* root, int v, int d) {
        if( d == 1 )
            return new TreeNode(v,root,nullptr);

        // BFS
        queue<pair<TreeNode*,int>> q;
        q.push({root,1});
        pair<TreeNode*,int> qe;
        while( !q.empty() ) {
            qe = q.front();
            q.pop();
            if( qe.second == d-1 ) {
                // left
                TreeNode* t = new TreeNode(v,qe.first->left,nullptr);
                qe.first->left = t;
                // right
                t = new TreeNode(v,nullptr,qe.first->right);
                qe.first->right = t;
                continue;
            }
            if( qe.first->left != nullptr  ) q.push({qe.first->left,qe.second+1});
            if( qe.first->right != nullptr ) q.push({qe.first->right,qe.second+1});
        }
        return root;
    }
};
