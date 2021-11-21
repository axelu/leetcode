
// 1820. Maximum Number of Accepted Invitations
// https://leetcode.com/problems/maximum-number-of-accepted-invitations/




class Solution {
private:
    int m,n;

    bool bpm(vector<vector<int>>& grid, int u, int seen[], int matchR[]) {
        // return true if the boy u can be matched with a girl

        // try every girl one by one
        for(int v = 0; v < n; v++) {

            // if boy u can invite girl v and v is not visited
            if( grid[u][v] && !seen[v]) {
                // mark girl v as visited
                seen[v] = true;

                // if girl v is not assigned to a boy OR
                // the previously assigned boy for girl v (which is matchR[v])
                // has an alternate girl available.
                // since girl v is marked as visited, the
                // recursive call will not get girl v again
                if( matchR[v] < 0 || bpm(grid,matchR[v],seen,matchR) ) {
                    matchR[v] = u;
                    return true;
                }
            }
        }
        return false;
    }


public:
    int maximumInvitations(vector<vector<int>>& grid) {
        m = grid.size();    // rows = boys
        n = grid[0].size(); // cols = girls

        // Bipartite Graph: boys are one part, girls are the other part
        // Maximum Bipartite Matching problem

        // array to keep track of boys assigned to girls
        // the value of matchR[j] is the boy index assigned to girl j
        int matchR[n];
        memset(matchR,-1,sizeof matchR);

        int ans = 0;
        int seen[n];
        for(int u = 0; u < m; u++) {
            // all girls are initially invitable for the next boy
            memset(seen,0,sizeof seen);

            if( bpm(grid,u,seen,matchR) )
                ++ans;
        }

        return ans;
    }
};
