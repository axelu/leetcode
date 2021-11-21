
// 1902. Depth of BST Given Insertion Order
// https://leetcode.com/problems/depth-of-bst-given-insertion-order/





// TLE case 65/70
/*
class Solution {
private:
    // Definition for a binary tree node.
    struct TreeNode {
        int val;
        TreeNode *left;
        TreeNode *right;
        TreeNode() : val(0), left(nullptr), right(nullptr) {}
        TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
        TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
    };

    int ans;

    void insert(TreeNode* root, int val, int depth) {
        ++depth;
        int p = root->val;
        if( val < p ) {
            if( root->left == nullptr ) {
                root->left = new TreeNode(val);
                ans = max(ans,depth+1);
                return;
            } else {
                insert(root->left,val,depth);
            }
        } else {
            // val > p
            if( root->right == nullptr ) {
                root->right = new TreeNode(val);
                ans = max(ans,depth+1);
                return;
            } else {
                insert(root->right,val,depth);
            }
        }
    }
public:
    int maxDepthBST(vector<int>& order) {
        int n = order.size();
        ans = 1;
        if( n == 1 )
            return ans;

        TreeNode* root = new TreeNode(order[0]);
        for(int i = 1; i < n; ++i)
            insert(root,order[i],0);

        return ans;
    }
};
*/
class Solution {
public:
    int maxDepthBST(vector<int>& order) {
        int n = order.size();
        int ans = 1;
        if( n == 1 )
            return ans;

        // binary search tree map
        map<int,int> bst;           // val,depth
        bst.insert({order[0],1});   // root at level 1

        map<int,int>::iterator lb,ub;
        int val,lftDepth,rgtDepth,depth;

        for(int i = 1; i < n; ++i) {
            val = order[i];
            lb = bst.lower_bound(val);
            lftDepth = 0;
            if( lb != bst.end() ) {
                if( lb != bst.begin())
                    lftDepth = (prev(lb))->second;
            } else
                lftDepth = bst.rbegin()->second;


            ub = bst.upper_bound(val);
            rgtDepth = 0;
            if( ub != bst.end() )
                rgtDepth = ub->second;


            depth = max(lftDepth,rgtDepth) + 1;
            ans = max(ans,depth);
            bst.insert({val,depth});
        }

        return ans;
    }
};
