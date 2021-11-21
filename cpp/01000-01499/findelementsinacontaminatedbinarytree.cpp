
// 1261. Find Elements in a Contaminated Binary Tree
// https://leetcode.com/problems/find-elements-in-a-contaminated-binary-tree/


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
class FindElements {
public:
    FindElements(TreeNode* root) {
        _recover(root, nullptr);
    }

    bool find(int target) {
        return ( bst.find(target) != bst.end() ) ? true : false;
    }
private:
    unordered_set<int> bst = {};
    void _recover(TreeNode* root, TreeNode* parent) {
        if( root == nullptr ) return;

        if( parent == nullptr ) {
            root->val = 0;
        } else if ( parent->left == root ) {
            root->val = parent->val * 2 + 1;
        } else {
            root->val = parent->val * 2 + 2;
        }

        bst.insert(root->val);

        _recover(root->left, root);
        _recover(root->right, root);
    }
};

/**
 * Your FindElements object will be instantiated and called as such:
 * FindElements* obj = new FindElements(root);
 * bool param_1 = obj->find(target);
 */
