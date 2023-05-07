
// 2641. Cousins in Binary Tree II
// https://leetcode.com/problems/cousins-in-binary-tree-ii/




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
private:
    int process(TreeNode* tn, queue<pair<TreeNode*,TreeNode*>>& q, int& sum) {
        int t = 0;

        if( tn != nullptr ) {
            t = tn->val;

            pair<TreeNode*,TreeNode*> p = make_pair(nullptr,nullptr);

            if( tn->left != nullptr ) {
                sum += tn->left->val;
                p.first = tn->left;
            }
            if( tn->right != nullptr ) {
                sum += tn->right->val;
                p.second = tn->right;
            }
            if( p.first != nullptr || p.second != nullptr )
                q.push(p);
        }

        return t;
    }

public:
    TreeNode* replaceValueInTree(TreeNode* root) {

        queue<pair<TreeNode*,TreeNode*>> q;
        q.push({root,nullptr});
        int sum = root->val;    // sum of node vals on current level

        while( !q.empty() ) {

            queue<pair<TreeNode*,TreeNode*>> q_new;
            int sum_new = 0;

            while( !q.empty() ) {
                int t = 0;

                t += process(q.front().first, q_new, sum_new);
                t += process(q.front().second, q_new, sum_new);

                // update node values
                if( q.front().first != nullptr )
                    q.front().first->val = sum - t;
                if( q.front().second != nullptr )
                    q.front().second->val = sum - t;

                q.pop();
            }

            q = q_new;
            sum = sum_new;
        }

        return root;
    }
};
