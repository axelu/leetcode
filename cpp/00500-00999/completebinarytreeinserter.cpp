// 919. Complete Binary Tree Inserter
// https://leetcode.com/problems/complete-binary-tree-inserter/



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
class CBTInserter {
public:
    CBTInserter(TreeNode* root) {
        mytree = root;
    }

    int insert(int v) {
        h = 0;
        lml = nullptr;
        inserted = false;
        return walk(mytree, 0, v);
    }

    TreeNode* get_root() {
        return mytree;
    }
private:
    TreeNode* mytree;
    int h;          // running height of tree, 0 indexed
    TreeNode* lml;  // left most leaf node
    bool inserted;

    int walk(TreeNode * root, int y, int v) {
        if( inserted ) return -1;
        h = max(h, y);

        if( root->left != nullptr && root->right == nullptr ) {
                root->right = new TreeNode(v);
                inserted = true;
                return root->val;
        }

        if( root->left == nullptr && root->right == nullptr ) {
            // leaf node
            if( lml == nullptr ) lml = root;
        }

        if( y == h - 1 ) {
            if( root->left == nullptr ) {
                root->left = new TreeNode(v);
                inserted = true;
                return root->val;
            } else if (root->right == nullptr ) {
                root->right = new TreeNode(v);
                inserted = true;
                return root->val;
            }
        }

        int l = ( root->left != nullptr ) ? walk(root->left, y + 1, v) : -1;
        int r = ( root->right != nullptr ) ? walk(root->right, y + 1, v) : -1;

        if( y == 0 && l == -1 && r == -1 ) {
            lml->left = new TreeNode(v);
            return lml->val;
        }

        return ( l == -1 ) ? r : l;
    }
};

/**
 * Your CBTInserter object will be instantiated and called as such:
 * CBTInserter* obj = new CBTInserter(root);
 * int param_1 = obj->insert(v);
 * TreeNode* param_2 = obj->get_root();
 */
