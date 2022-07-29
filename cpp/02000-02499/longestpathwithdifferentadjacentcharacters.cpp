
// 2246. Longest Path With Different Adjacent Characters
// https://leetcode.com/problems/longest-path-with-different-adjacent-characters/



class Solution {
private:
    int ans;

    int dfs(vector<int> g[], int u, int c, string& s) {
        // c is the char assigned to our parent
        // if we have the same char as out parent
        // then the answer upward is 0


        // there can be a path through me
        // we need to capture the largest and second largest value
        int a = 0; // largest value seen
        int b = 0; // second largest value seen

        for(int i = 0; i < g[u].size(); ++i) {
            int v = g[u][i];
            int t = dfs(g,v,s[u],s);
            if( t >= a ) {
                b = a;
                a = t;
            } else if( t > b )
                b = t;
        }

        ans = max(ans,a+b+1);

        return c != s[u] ? a + 1 : 0;
    }
public:
    int longestPath(vector<int>& parent, string s) {
        int n = parent.size();

        vector<int> g[n];
        for(int i = 1; i < n; ++i)
            g[parent[i]].push_back(i);

        ans = 0;
        int t = dfs(g,0,'#',s);

        return max(ans,t);
    }
};
