
// 1367. Linked List in Binary Tree
// https://leetcode.com/problems/linked-list-in-binary-tree/



/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
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
    bool _isSubPath(TreeNode* root, ListNode* head) {
        if( root == nullptr && head == nullptr ) return true;
        if( root == nullptr ) return false;
        if( head == nullptr ) return true;
        if( root->val != head->val ) return false;

        if( _isSubPath(root->left,head->next) ) return true;
        return _isSubPath(root->right,head->next);
    }

    bool dfs(TreeNode* root, ListNode* head) {
        if( root == nullptr ) return false;

        if( root->val == head->val ) {
            if( _isSubPath(root->left,head->next) ) return true;
            if( _isSubPath(root->right,head->next) ) return true;
        }

        if( dfs(root->left,head) ) return true;
        return dfs(root->right,head);
    }

public:
    bool isSubPath(ListNode* head, TreeNode* root) {
       return dfs(root,head);
    }
};
