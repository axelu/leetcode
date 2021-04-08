
// 272. Closest Binary Search Tree Value II
// https://leetcode.com/problems/closest-binary-search-tree-value-ii/


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
    vector<int> closestKValues(TreeNode* root, double target, int k) {

        // BFS
        priority_queue<pair<double,int>> pq;
        queue<TreeNode*> q;
        TreeNode* qe;
        q.push(root);
        double diff;
        while(!q.empty()) {
            qe = q.front();
            q.pop();

            if( pq.size() < k ) {
                // if we don't have enough values collected yet,
                // we add the current value to the answer and its children for processing
                pq.push({abs(qe->val - target),qe->val});
                if( nullptr != qe->left ) q.push(qe->left);
                if( nullptr != qe->right ) q.push(qe->right);
            } else {
                diff = abs(qe->val - target);
                if( diff < pq.top().first ) {
                    pq.pop();
                    pq.push({diff,qe->val});
                    if( nullptr != qe->left ) q.push(qe->left);
                    if( nullptr != qe->right ) q.push(qe->right);
                } else if( qe->val > target ) {
                    if( nullptr != qe->left ) q.push(qe->left);
                } else {
                    if( nullptr != qe->right ) q.push(qe->right);
                }
            }
        }

        vector<int> ans(k);
        int i = 0;
        while( !pq.empty() ) {
            ans[i] = pq.top().second;
            pq.pop();
            ++i;
        }

        return ans;
    }
};
