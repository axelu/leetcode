
// 515. Find Largest Value in Each Tree Row
// https://leetcode.com/problems/find-largest-value-in-each-tree-row/




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
    vector<int> largestValues(TreeNode* root) {
        vector<int> ans;
        if( root == nullptr ) return ans;

        queue<pair<TreeNode*,int>> q;
        q.push({root,1});
        int pl = 1, mx = root->val;
        pair<TreeNode*,int> qe;
        while( !q.empty() ) {
            qe = q.front();
            q.pop();
            if( qe.second != pl ) {
                ans.push_back(mx);
                mx = INT_MIN;
                pl = qe.second;
            }
            mx = max(mx,qe.first->val);
            if( qe.first->left != nullptr ) q.push({qe.first->left,qe.second+1});
            if( qe.first->right != nullptr ) q.push({qe.first->right,qe.second+1});
        }
        ans.push_back(mx);
        return ans;
    }
};
