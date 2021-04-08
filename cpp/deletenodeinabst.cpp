

// day 31 August 2020 challenge
// Delete Node in a Binary Search Tree
// https://leetcode.com/explore/challenge/card/august-leetcoding-challenge/553/week-5-august-29th-august-31st/3443/
// https://leetcode.com/problems/delete-node-in-a-bst/



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
    TreeNode* deleteNode(TreeNode* root, int key) {
        if( root == nullptr ) return root;
        if( root->left == nullptr && root->right == nullptr )
            return ( root->val == key ) ? nullptr : root;

		if (key < root->val) {
			root->left = deleteNode(root->left, key);
		} else if (key > root->val) {
			root->right = deleteNode(root->right, key);
		} else {
            // value matches
            if (root->left == nullptr) {
                // if only one child, it can replace the node
				TreeNode *tn = root->right;
				delete (root);
				return tn;
			} else if (root->right == nullptr) {
                // if only one child, it can replace the node
				TreeNode *tn = root->left;
				delete (root);
				return tn;
			} else {
                TreeNode *tn = root->right;
                while ( tn != nullptr && tn->left != nullptr ) {
                    tn = tn->left;
                }
                root->val = tn->val;
                root->right = deleteNode(root->right, tn->val);
			}
		}
		return root;
    }
};
