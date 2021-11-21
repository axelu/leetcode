
// 1257. Smallest Common Region
// https://leetcode.com/problems/smallest-common-region/
// solution passes, but see smallestcommonregion2.cpp for faster solution




class Solution {
private:
    struct TreeNode {
        string val;
        vector<TreeNode*> children;
        TreeNode(string s) : val(s), children({}) {}
    };

    // Lowest Common Ancestor (LCA) in N-ary tree
    TreeNode* LCA(TreeNode* root, string key1, string key2) {
        if( nullptr == root )
            return nullptr;

        if( root->val == key1 || root->val == key2 )
            return root;

        TreeNode* lft_lca = nullptr;
        TreeNode* rgt_lca = nullptr;

        for(int i = 0; i < root->children.size(); ++i) {
            if( lft_lca == nullptr ) {
                lft_lca = LCA(root->children[i],key1,key2);
            } else {
                rgt_lca = LCA(root->children[i],key1,key2);
                if( rgt_lca != nullptr )
                    break;
            }
        }

        // if both of the above calls return something other than nullptr,
        // then one key is present in one subtree and
        // other key is present in other subtree, hence the
        // current node is the Lowest Common Ancestor (LCA) to both keys
        if( nullptr != lft_lca && nullptr != rgt_lca )
            return root;

        // else check if left subtree or right subtree is LCA
        return lft_lca;
    }


public:
    string findSmallestRegion(vector<vector<string>>& regions, string region1, string region2) {

        TreeNode* root = new TreeNode(regions[0][0]);
        unordered_map<string,TreeNode*> um;
        um.insert({regions[0][0],root});

        for(int i = 0; i < regions.size(); ++i) {
            TreeNode* parent = um.find(regions[i][0])->second;

            for(int j = 1; j < regions[i].size(); ++j) {
                TreeNode* tn = new TreeNode(regions[i][j]);
                parent->children.push_back(tn);
                um.insert({regions[i][j],tn});
            }
        }

        return LCA(root,region1,region2)->val;
    }
};
