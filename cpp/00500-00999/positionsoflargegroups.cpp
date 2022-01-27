
// 830. Positions of Large Groups
// https://leetcode.com/problems/positions-of-large-groups/


class Solution {
public:
    vector<vector<int>> largeGroupPositions(string s) {
        int n = s.size();

        vector<vector<int>> ans;
        char c;
        int l;
        for(int i = 0; i < n; ++i) {
            if( i == 0 ) {
                c = s[i];
                l = 0;
            }
            if( s[i] != c ) {
                if( i - l >= 3 )
                    ans.push_back({l,i-1});
                c = s[i];
                l = i;
            }
        }
        // finish up
        if( n - l >= 3 )
            ans.push_back({l,n-1});
        return ans;
    }
};
