
// 455. Assign Cookies
// https://leetcode.com/problems/assign-cookies/



class Solution {
public:
    int findContentChildren(vector<int>& g, vector<int>& s) {
        int m = s.size(); // number of cookies
        if( m == 0 ) return 0;
        int n = g.size(); // number of children
        sort(g.begin(),g.end());
        sort(s.begin(),s.end());

        int is = 0;
        int ans = 0;
        for(int ig = 0; ig < n; ++ig) {
            while( is < m && s[is] < g[ig] )
                ++is;
            if( is == m ) break;
            ++ans;
            ++is;
        }
        return ans;
    }
};
