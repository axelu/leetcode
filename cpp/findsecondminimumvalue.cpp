
// 671. Second Minimum Node In a Binary Tree
// https://leetcode.com/problems/second-minimum-node-in-a-binary-tree/


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
    int findSecondMinimumValue(TreeNode* root) {
        if( nullptr == root ) return -1;
        int mn = root->val;

        // constraint are small, so brute force
        set<int> s;
        // BFS
        queue<TreeNode*> q;
        q.push(root);
        TreeNode* qe;
        while(!q.empty()) {
            qe = q.front();
            q.pop();
            s.insert(qe->val);
            if( nullptr != qe->left ) {
                q.push(qe->left);
                q.push(qe->right);
            }
        }
        return s.size() < 2 ? -1 : *next(s.begin());
    }
};
