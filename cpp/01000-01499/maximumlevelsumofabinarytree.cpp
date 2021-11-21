
// 1161. Maximum Level Sum of a Binary Tree
// https://leetcode.com/problems/maximum-level-sum-of-a-binary-tree/



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
    int maxLevelSum(TreeNode* root) {

        pair<int,int> ans; // sum,level

        // BFS
        queue<pair<TreeNode*,int>> q;
        pair<TreeNode*,int> qe; // TreeNode*,level
        int sum = 0, curLevel = 1;
        ans = {root->val,1}; // root
        q.push({root,1});
        while( !q.empty() ) {
            qe = q.front();
            q.pop();
            if( qe.second != curLevel ) {
                // first node of new level
                if( sum > ans.first ) {
                    ans.first = sum;
                    ans.second = curLevel;
                }
                // reset
                sum = 0;
                curLevel = qe.second;
            }
            sum += qe.first->val;
            if( nullptr != qe.first->left )  q.push({qe.first->left, curLevel+1});
            if( nullptr != qe.first->right ) q.push({qe.first->right,curLevel+1});
        }

        return sum > ans.first ? curLevel : ans.second;
    }
};
