
// 2764. is Array a Preorder of Some Binary Tree
// https://leetcode.com/problems/is-array-a-preorder-of-some-binary-tree/





class Solution {
private:
    struct TreeNode {
        int val;
        TreeNode *left;
        TreeNode *right;
        TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    };

    // preorder traversal
    bool dfs(TreeNode* tn, vector<vector<int>>& nodes, int& i) {
        if( nodes[i][0] != tn->val )
            return false;

        if( tn->left != nullptr ) {
            ++i;
            if( !dfs(tn->left,nodes,i) )
                return false;
        }
        if( tn->right != nullptr ) {
            ++i;
            if( !dfs(tn->right,nodes,i) )
                return false;
        }

        return true;
    }

public:
    bool isPreorder(vector<vector<int>>& nodes) {
        // the 1st node must be the root
        if( nodes[0][1] != -1 )
            return false;

        int n = nodes.size();
        if( n == 1 )
            return true;

        // from the constraints: The input is generated such that nodes make a binary tree.
        // build the tree from nodes
        unordered_map<int,TreeNode*> um;
        TreeNode* root = new TreeNode(nodes[0][0]);
        um.insert({nodes[0][0],root});
        for(int i = 1; i < n; ++i) {
            TreeNode* tn = new TreeNode(nodes[i][0]);
            // locate the parent
            if( nodes[i][1] == -1 )
                return false;
            auto f = um.find(nodes[i][1]);
            if( f == um.end() )
                return false;

            bool lft = false;
            if( f->second->left == nullptr ) {
                f->second->left = tn;
                lft = true;
            }
            if( !lft ) {
                if( f->second->right != nullptr )
                    return false;
                else
                    f->second->right = tn;
            }

            auto p = um.insert({nodes[i][0],tn});
            if( !p.second )
                return false;
        }

        int i = 0;
        return dfs(root,nodes,i);
    }
};
