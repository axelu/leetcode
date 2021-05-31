
// 1602. Find Nearest Right Node in Binary Tree
// https://leetcode.com/problems/find-nearest-right-node-in-binary-tree/




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
    TreeNode* findNearestRightNode(TreeNode* root, TreeNode* u) {
       if( root == u ) return nullptr;

        bool foundU = false;
        queue<pair<TreeNode*,int>> q; // TreeNode*,level
        int level = 0;
        q.push({root,level});
        pair<TreeNode*,int> qe;
        while(!q.empty()) {
            qe = q.front();
            q.pop();

            if( foundU && level != qe.second ) return nullptr;
            if( foundU && level == qe.second ) return qe.first;
            if( qe.first == u ) foundU = true;
            level = qe.second;
            if( foundU ) continue;
            if( qe.first->left  != nullptr ) q.push({qe.first->left,level+1});
            if( qe.first->right != nullptr ) q.push({qe.first->right,level+1});
        }
        return nullptr;
    }
};
