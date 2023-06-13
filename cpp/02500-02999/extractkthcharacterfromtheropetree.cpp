
// 2689. Extract Kth Character From The Rope Tree
// https://leetcode.com/problems/extract-kth-character-from-the-rope-tree/



/**
 * Definition for a rope tree node.
 * struct RopeTreeNode {
 *     int len;
 *     string val;
 *     RopeTreeNode *left;
 *     RopeTreeNode *right;
 *     RopeTreeNode() : len(0), val(""), left(nullptr), right(nullptr) {}
 *     RopeTreeNode(string s) : len(0), val(std::move(s)), left(nullptr), right(nullptr) {}
 *     RopeTreeNode(int x) : len(x), val(""), left(nullptr), right(nullptr) {}
 *     RopeTreeNode(int x, RopeTreeNode *left, RopeTreeNode *right) : len(x), val(""), left(left), right(right) {}
 * };
 */
class Solution {
private:
    char dfs(RopeTreeNode* root, int k) {
        if( root->len == 0 ) {
            // leaf node
            // return the kth char, 1-indexed
            return root->val[k-1];
        }

        int left = 0; // number of chars in left child
        // check if we need to go right or left
        if( root->left != nullptr ) {
            left = root->left->len;
            if( left == 0 ) {
                left = root->left->val.size();
            }
            if( left >= k )
                return dfs(root->left, k);
        }

        // if we are still here go right
        k = k - left;
        return dfs(root->right,k);
    }

public:
    char getKthCharacter(RopeTreeNode* root, int k) {
        return dfs(root,k);
    }
};
