
// 1257. Smallest Common Region
// https://leetcode.com/problems/smallest-common-region/

class Solution {
private:
        
    // Lowest Common Ancestor (LCA) in N-ary tree
    string LCA(unordered_map<string,int>& um, string& root, string& key1, string& key2,
               vector<vector<string>>& regions) {

        if( root == key1 || root == key2 )
            return root;
            
        string lft_lca = "";
        string rgt_lca = "";
        
        auto f = um.find(root);
        if( f == um.end() )
            return "";
        int i = f->second;
        
        for(int j = 1; j < regions[i].size(); ++j) {
            if( lft_lca.empty() ) {
                lft_lca = LCA(um,regions[i][j],key1,key2,regions);
            } else {
                rgt_lca = LCA(um,regions[i][j],key1,key2,regions);
                if( !rgt_lca.empty() )
                    break;
            }
        }
        
        // if both of the above calls return something other than nullptr,
        // then one key is present in one subtree and
        // other key is present in other subtree, hence the
        // current node is the Lowest Common Ancestor (LCA) to both keys
        if( !lft_lca.empty() && !rgt_lca.empty() ) 
            return root;

        // else check if left subtree or right subtree is LCA
        return lft_lca;
    }

    
public:
    string findSmallestRegion(vector<vector<string>>& regions, string region1, string region2) {
        unordered_map<string,int> um;
        for(int i = 0; i < regions.size(); ++i)
            um.insert({regions[i][0],i});
        
        return LCA(um,regions[0][0],region1,region2,regions);
    }
};
