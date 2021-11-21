
// 1273. Delete Tree Nodes
// https://leetcode.com/problems/delete-tree-nodes/




class Solution {
private:
    struct TreeNode {
        int val;
        int sum; // subtree sum including value of node itself
        vector<TreeNode*> children;
        TreeNode() : val(-100001), sum(0), children({}) {}
        TreeNode(int x) : val(x), sum(0), children({}) {}
    };

    TreeNode* buildTree(int nodes, vector<int>& parent, vector<int>& value) {
        TreeNode* t[nodes];
        int seen[nodes]; memset(seen,0,sizeof seen);
        TreeNode* root;
        TreeNode* tn;
        TreeNode* pt;
        for(int i = 0; i < nodes; ++i) {
            // value
            if( !seen[i] ) {
                tn = new TreeNode(value[i]);
                t[i] = tn;
                seen[i] = 1;
            } else {
                tn = t[i];
                tn->val = value[i];
            }
            // parent
            if( parent[i] == -1 ) {
                root = t[i];
            } else {
                if( !seen[parent[i]] ) {
                    pt = new TreeNode();
                    pt->children.push_back(tn);
                    t[parent[i]] = pt;
                    seen[parent[i]] = 1;
                } else {
                    pt = t[parent[i]];
                    pt->children.push_back(tn);
                }
            }
        }

        return root;
    }

    int subtreeSum(TreeNode* root) {
        int s = root->val;
        for(int i = 0; i < root->children.size(); ++i)
            s += subtreeSum(root->children[i]);
        root->sum = s;
        return s;
    }

    int ans;
    void count(TreeNode* root) {
        if( root->sum != 0 ) {
            ++ans;
            for(int i = 0; i < root->children.size(); ++i)
                count(root->children[i]);
        }
    }

public:
    int deleteTreeNodes(int nodes, vector<int>& parent, vector<int>& value) {
        if( nodes == 0 ) return 0;

        TreeNode* root = buildTree(nodes,parent,value);
        subtreeSum(root);
        ans = 0;
        count(root);
        return ans;
    }
};
