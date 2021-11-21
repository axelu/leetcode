
// 1469. Find All The Lonely Nodes
// https://leetcode.com/problems/find-all-the-lonely-nodes/


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
    vector<int> getLonelyNodes(TreeNode* root) {
        vector<int> ans;
        queue<TreeNode*> q;
        q.push(root);
        TreeNode* qe;
        while(!q.empty()) {
            qe = q.front();
            q.pop();

            if( qe->left != nullptr ) {
                q.push(qe->left);
                if( qe->right == nullptr )
                    ans.push_back(qe->left->val);
            }
            if( qe->right != nullptr ) {
                q.push(qe->right);
                if( qe->left == nullptr )
                    ans.push_back(qe->right->val);
            }
        }

        return ans;
    }
};
