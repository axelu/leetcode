
// 1110. Delete Nodes and Return Forrest
// https://leetcode.com/problems/delete-nodes-and-return-forest/


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
    vector<TreeNode*> delNodes(TreeNode* root, vector<int>& to_delete) {
        vector<TreeNode*> ans;
        if( nullptr == root ) return ans; // nothing to delete
        if( to_delete.empty() ) {
            ans.push_back(root);
            return ans;
        }

        sort(begin(to_delete),end(to_delete));
        // BFS
        queue<pair<TreeNode*,TreeNode*>> q;
        pair<TreeNode*,TreeNode*> qe; // node,parent
        q.push({root,nullptr});
        vector<int>::iterator tdBegin = begin(to_delete);
        vector<int>::iterator tdEnd   = end(to_delete);
        bool toBeDeleted;
        TreeNode* parent;
        while(!q.empty()) {
            qe = q.front();
            q.pop();

            // delete this node?
            toBeDeleted = binary_search(tdBegin,tdEnd,qe.first->val);
            if( toBeDeleted ) {
                parent = nullptr;
                // tell the parent, if there is a parent
                if( nullptr != qe.second ) {
                    if( qe.second->left != nullptr && qe.second->left == qe.first )
                        qe.second->left = nullptr;
                    else
                        qe.second->right = nullptr;
                }
            } else {
                parent = qe.first;
                // if I am not going to be deleted and I don't have a parent, I am part of the answer
                if( nullptr == qe.second )
                    ans.push_back(qe.first);
            }

            if( nullptr != qe.first->left )  q.push({qe.first->left,parent});
            if( nullptr != qe.first->right ) q.push({qe.first->right,parent});
        }

        return ans;
    }
};
