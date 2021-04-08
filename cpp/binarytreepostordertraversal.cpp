
// 145. Binary Tree Postorder Traversal
// https://leetcode.com/problems/binary-tree-postorder-traversal/





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
// inspired by https://www.geeksforgeeks.org/iterative-postorder-traversal/
class Solution {
public:
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> ans;
        if( root == nullptr ) return ans;

        // iterative
        stack<TreeNode*> stck1,stck2;
        stck1.push(root);
        TreeNode* curr;
        while(!stck1.empty()) {
            curr = stck1.top();
            stck1.pop();
            stck2.push(curr);
            if( curr->left != nullptr )
                stck1.push(curr->left);
            if( curr->right != nullptr )
                stck1.push(curr->right);
        }

        while(!stck2.empty()) {
            ans.push_back(stck2.top()->val);
            stck2.pop();
        }

        return ans;
    }
};
