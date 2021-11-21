
// 103. Binary Tree Zigzag Level Order Traversal
// https://leetcode.com/problems/binary-tree-zigzag-level-order-traversal/




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
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        vector<vector<int>> ans;
        if( root == nullptr ) return ans;

        // BFS
        queue<pair<TreeNode*,int>> q;
        pair<TreeNode*,int> qe;
        q.push({root,0});
        int currLevel = 0;
        vector<int> v;
        while(!q.empty()) {
            qe = q.front();
            q.pop();
            if( qe.second != currLevel ) {
                ans.push_back(v);
                v.clear();
                currLevel = qe.second;
            }
            if( currLevel % 2 == 0 ) v.push_back(qe.first->val);
            else v.insert(v.begin(),qe.first->val);
            if( qe.first->left != nullptr )
                q.push({qe.first->left,qe.second+1});
            if( qe.first->right != nullptr )
                q.push({qe.first->right,qe.second+1});
        }
        // finish up
        if( !v.empty() ) ans.push_back(v);
        return ans;
    }
};
