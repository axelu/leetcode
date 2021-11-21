
// 77. Combinations
// https://leetcode.com/problems/combinations/




class Solution {
private:
    /*
    void genCombinations(vector<int>& v, int i, int k, vector<int>& combination, vector<vector<int>>& ans) {
        // this approach is an adaption of generating subsequences
        if( i == v.size() ) {
            if( combination.size() == k )
                ans.push_back(combination);
            return;
        }
        
        // we have a choice
        // don't include the current element
        genCombinations(v,i+1,k,combination,ans);
        
        
        // including the current element
        if( combination.size() == k )
            return;
        combination.push_back(v[i]);
        genCombinations(v,i+1,k,combination,ans);
        combination.pop_back();
    }
    */
    
    int N,K;
    
    void genCombinations(vector<int>& v, int depth, int i, vector<int>& combination, vector<vector<int>>& ans) {
        if( depth == K ) {
            ans.push_back(combination);
            return;
        }
        
        int jmax = N-K+depth;
        for(int j = i; j <= jmax; ++j) {
            combination[depth] = v[j];
            genCombinations(v,depth+1,j+1,combination,ans);
        }
    }
    
public:
    vector<vector<int>> combine(int n, int k) {
        // 1 <= n <= 20
        // 1 <= k <= n
        
        // all possible combinations of k length
        
        vector<vector<int>> ans;
        
        if( k == 1 ) {
            for(int i = 1; i <= n; ++i)
                ans.push_back({i});
            return ans;    
        }
            
        vector<int> v(n);
        for(int i = 1; i <= n; ++i)
            v[i-1] = i;
        
        if( k == n ) {
            ans.push_back(v);
            return ans;
        }
                
        // vector<int> combination;
        // genCombinations(v,0,k,combination,ans);
        
        vector<int> combination(k);
        N = n;
        K = k;
        genCombinations(v,0,0,combination,ans);
                
        return ans;
    }
};
