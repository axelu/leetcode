
// 1284. Minimum Number of Flips to Convert Binary Matrix to Zero Matrix
// https://leetcode.com/problems/minimum-number-of-flips-to-convert-binary-matrix-to-zero-matrix/



class Solution {
private:
    void printBinary(long x, int c) {

        /* for(int i = c-1; i >= 0; --i) {
            if( x & (1UL << i) ) cout << 1;
            else cout << 0;
        }
        */
        for(int i = 0; i < c; ++i) {
            if( x & (1UL << i) ) cout << 1;
            else cout << 0;
        }
        cout << endl;
    }

    int m,n;

    int get_state(vector<vector<int>>& mat) {
        int state = 0;
        for(int i = 0; i < m; ++i)
            for(int j = 0; j < n; ++j)
                if( mat[i][j] )
                    state |= 1 << (i*n+j);
        return state;
    }

    // directions   R  D  L  U
    int dirR[4] = { 0, 1, 0,-1};
    int dirC[4] = { 1, 0,-1, 0};

    int new_state(int state, int k) {
        state ^= 1 << k;
        int i = k / n;
        int j = k % n;
        for(int f = 0; f < 4; ++f) {
            int i_new = i + dirR[f];
            if( i_new < 0 || i_new == m )
                continue;

            int j_new = j + dirC[f];
            if( j_new < 0 || j_new == n )
                continue;

            int k_new = i_new * n + j_new;
            state ^= 1 << k_new;
        }
        return state;
    }
public:
    int minFlips(vector<vector<int>>& mat) {
        m = mat.size();     // rows
        n = mat[0].size();  // cols

        int seen[512][512]; // state,flipped
        memset(seen,0,sizeof seen);

        queue<array<int,3>> q; // state,flipped,steps
        int initial_state = get_state(mat);
        q.push({initial_state,0,0});
        // seen[state][0] = 1;
        while( !q.empty() ) {
            auto[state,flipped,steps] = q.front();
            q.pop();
            // printBinary(state,m*n);

            if( state == 0 )
                return steps;

            for(int k = 0; k < m*n; ++k) {
                // if we haven't flipped the kth bit, flip it
                if( !((flipped >> k) & 1) ) {
                    int flipped_new = flipped | (1 << k);
                    int state_new = new_state(state,k);
                    // cout << "flipped " << k << "th bit" << endl;
                    // printBinary(state_new,m*n);

                    if( seen[state_new][flipped_new] )
                        continue;

                    seen[state_new][flipped_new] = 1;
                    q.push({state_new,flipped_new,steps+1});
                }
            }
        }

        return -1;
    }
};
