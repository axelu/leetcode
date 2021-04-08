
// 547. Number of Provinces
// https://leetcode.com/problems/number-of-provinces/



class Solution {
private:
    void dfs(int v, vector<vector<int>>& isConnected, int seen[]) {
        if( seen[v] ) return;
        seen[v] = 1;
        for(int i = 0; i < isConnected.size(); ++i)
            if( isConnected[v][i] ) dfs(i,isConnected,seen);
    }
public:
    int findCircleNum(vector<vector<int>>& isConnected) {
        int n = isConnected.size();
        if( n == 1 ) return 1;

        int seen[n]; memset(seen,0,sizeof seen);
        int ans = 0;
        for(int i = 0; i < n; ++i)
            if( !seen[i] ) {
                dfs(i,isConnected,seen);
                ++ans;
            }
        return ans;
    }
};
