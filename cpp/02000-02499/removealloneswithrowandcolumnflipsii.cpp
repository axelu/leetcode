
// 2174. Remove All Ones With Row and Column Flips II
// https://leetcode.com/problems/remove-all-ones-with-row-and-column-flips-ii/



class Solution {
private:
    int m,n;

    int get_state(vector<vector<int>>& mat) {
        int state = 0;
        for(int i = 0; i < m; ++i)
            for(int j = 0; j < n; ++j)
                if( mat[i][j] )
                    state |= 1 << (i*n+j);
        return state;
    }

    int new_state(int state, int k) {
        int i = k / n;
        int j = k % n;
        // row i
        for(int j_new = 0; j_new < n; ++j_new) {
            int k_new = i * n + j_new;
            if( (state >> k_new) & 1 )
                state &= ~(1 << k_new);
        }
        // col j
        for(int i_new = 0; i_new < m; ++i_new) {
            int k_new = i_new * n + j;
            if( (state >> k_new) & 1 )
                state &= ~(1 << k_new);
        }
        return state;
    }

public:
    int removeOnes(vector<vector<int>>& grid) {
        m = grid.size();    // rows
        n = grid[0].size(); // cols

        int seen[32768]; // state
        memset(seen,0,sizeof seen);

        queue<array<int,2>> q; // state,steps
        int initial_state = get_state(grid);
        q.push({initial_state,0});
        // seen[state] = 1;
        while( !q.empty() ) {
            auto[state,steps] = q.front();
            q.pop();

            if( state == 0 )
                return steps;

            for(int k = 0; k < m*n; ++k)
                if( (state >> k) & 1 ) {
                    int state_new = new_state(state,k);

                    if( seen[state_new] )
                        continue;

                    seen[state_new] = 1;
                    q.push({state_new,steps+1});
                }
        }

        return -1; // satisfy compiler
    }
};
