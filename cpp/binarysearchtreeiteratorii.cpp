
// 1586. Binary Search Tree Iterator II
// https://leetcode.com/problems/binary-search-tree-iterator-ii/



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
class BSTIterator {
private:
    deque<int> nxt;
    stack<int> prv;
    int cur;

    void inorder(TreeNode* root) {
        if( root == nullptr ) return;
        inorder(root->left);
        nxt.push_back(root->val);
        inorder(root->right);
    }

public:
    BSTIterator(TreeNode* root) {
        inorder(root);
        cur = -1;
    }

    bool hasNext() {
        return !nxt.empty();
    }

    int next() {
        if( cur != -1 ) prv.push(cur);
        cur = nxt.front();
        nxt.pop_front();
        return cur;
    }

    bool hasPrev() {
        return !prv.empty();
    }

    int prev() {
        nxt.push_front(cur);
        cur = prv.top();
        prv.pop();
        return cur;
    }
};

/**
 * Your BSTIterator object will be instantiated and called as such:
 * BSTIterator* obj = new BSTIterator(root);
 * bool param_1 = obj->hasNext();
 * int param_2 = obj->next();
 * bool param_3 = obj->hasPrev();
 * int param_4 = obj->prev();
 */
