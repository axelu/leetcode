
// 156. Binary Tree Upside Down
// https://leetcode.com/problems/binary-tree-upside-down/


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
    TreeNode* upsideDownBinaryTree(TreeNode* root) {
        if( nullptr == root ) return nullptr;
        // constraint: every node in the given tree has either 0 or 2 children
        if( nullptr == root->left ) return root; // no left child means there is also no right child

        queue<array<TreeNode*,3>> q;
        array<TreeNode*,3> qe;
        q.push({root,nullptr,nullptr});
        TreeNode* tn,l,r;
        while( !q.empty() ) {
            qe = q.front();
            q.pop();
            tn = qe[0];

            // add left child to queue with the information it needs to perform its transformation
            // right child does not undergo any transformation of their children
            if( tn->left != nullptr )
                q.push({tn->left,tn->right,tn});

            // transform myself
            tn->left = qe[1];
            tn->right = qe[2];

            root = tn;
        }

        return root;

    }
};
