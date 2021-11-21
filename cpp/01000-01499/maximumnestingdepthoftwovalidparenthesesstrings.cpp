
// 1111. Maximum Nesting Depth of Two Valid Parentheses Strings
// https://leetcode.com/problems/maximum-nesting-depth-of-two-valid-parentheses-strings/





class Solution {
private:
    multimap<int,pair<int,int>> mm;


    int rec(int& idx, string& S, int depth) {
        int l = idx;
        ++idx;
        if( S[idx] == ')' ) {
            mm.insert({1,{l,idx}});
            return 1;
        }
        int ans = 0;
        while( S[idx] != ')' ) {
            ans = max(ans,rec(idx,S,depth+1));
            ++idx;
        }
        mm.insert({ans+1,{l,idx}});
        return ans+1;
    }

public:
    vector<int> maxDepthAfterSplit(string& seq) {
        int n = seq.size();
        vector<int> ans(n,0);

        int t = 1;
        int idx = 0;
        while( idx < n ) {
            t = max(t,rec(idx,seq,0));
            ++idx;
        }
        if( t == 1 ) return ans;

        t = t/2; // question states: "...split it into two disjoint subsequences..."
        for(auto it = mm.upper_bound(t); it != mm.end(); ++it) {
            ans[it->second.first]  = 1;
            ans[it->second.second] = 1;
        }

        return ans;
    }
};
