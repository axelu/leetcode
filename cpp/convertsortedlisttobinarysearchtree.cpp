
// Convert Sorted List to Binary Search Tree
// https://leetcode.com/problems/convert-sorted-list-to-binary-search-tree/



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
public:
    TreeNode* sortedListToBST(ListNode* head) {
        if( head == nullptr ) return nullptr;

        while( head != nullptr ) {
            v.push_back(head->val);
            head = head->next;
        }

        return _build(v.begin(), v.end());
    }
private:
    vector<int> v;

    TreeNode* _build(vector<int>::iterator itb, vector<int>::iterator ite) {
        if( ite - itb == 0 ) return nullptr;

        int h = (ite - itb) / 2;

        TreeNode* t = new TreeNode(*(itb + h));
        t->left = _build(itb, itb + h);
        t->right = _build(itb + h + 1, ite);

        return t;
    }
};
