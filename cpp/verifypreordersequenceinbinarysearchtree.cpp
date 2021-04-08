
// 255. Verify Preorder Sequence in Binary Search Tree
// https://leetcode.com/problems/verify-preorder-sequence-in-binary-search-tree/




class Solution {
private:
    struct TreeNode {
        int val;
        TreeNode *left;
        TreeNode *right;
        TreeNode() : val(0), left(nullptr), right(nullptr) {}
        TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
        TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
    };

    TreeNode* buildTree(vector<int>& preorder, int n, int& idx, long mn, long mx, int seen[]) {
        if( idx >= n ) return nullptr;

        TreeNode* root = nullptr;

        int val = preorder[idx];
        if( mn < val && mx > val ) {
            root = new TreeNode(val);
            seen[idx] = 1;
            ++idx;
            if( idx < n ) {
                // nodes in range {mn .. val}
                // go in left subtree
                root->left = buildTree(preorder,n,idx,mn,val,seen);
            }
            if( idx < n ) {
                // nodes in range {val .. mx}
                // go in right subtree
                root->right = buildTree(preorder,n,idx,val,mx,seen);
            }
        }
        return root;
    }

public:
    bool verifyPreorder(vector<int>& preorder) {
        int n = preorder.size();
        if( n < 2 ) return true;

        int seen[n]; memset(seen,0,sizeof seen);
        int idx = 0;
        TreeNode* root = buildTree(preorder,n,idx,INT_MIN-1L,INT_MAX+1L,seen);
        for(int i = 0; i < n; ++i)
            if( !seen[i] ) return false;
        return true;
    }
};
