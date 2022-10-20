
// 773. Sliding Puzzle
// https://leetcode.com/problems/sliding-puzzle/


class Solution {
private:
    int m = 2;
    int n = 3;

    int offset[2][3] = {{0,3,6},{9,12,15}};

    int get_state(vector<vector<int>>& mat) {
        int state = 0;
        for(int i = 0; i < m; ++i)
            for(int j = 0; j < n; ++j)
                state += (mat[i][j] << offset[i][j]);
        return state;
    }


public:
    int slidingPuzzle(vector<vector<int>>& board) {
        // 181896 max state
        //  22737 winning state

        int initial_state = get_state(board);
        int seen[181897];memset(seen,0,sizeof seen);
        queue<array<int,2>> q; // state,steps
        q.push({initial_state,0});
        seen[initial_state] = 1;
        while( !q.empty() ) {
            auto[state,steps] = q.front();
            q.pop();

            if( state == 22737 )
                return steps;

            int c0 = state & 7;
            int c1 = (state & 56) >>3;
            int c2 = (state & 448) >>6;
            int c3 = (state & 3584) >>9;
            int c4 = (state & 28672) >>12;
            int c5 = (state & 229376) >>15;
            // cout << c0 << " " << c1 << " " << c2 << " " << c3 << " " << c4 << " " << c5 << endl;

            int state_new;
            if( c0 == 0 ) {
                // swap c0 c1
                state_new = c1 + (c0<<3) + (c2<<6) + (c3<<9) + (c4<<12) + (c5<<15);
                if( !seen[state_new] ) {
                    seen[state_new] = 1;
                    q.push({state_new,steps+1});
                }
                // swap c0 c3
                state_new = c3 + (c1<<3) + (c2<<6) + (c0<<9) + (c4<<12) + (c5<<15);
                if( !seen[state_new] ) {
                    seen[state_new] = 1;
                    q.push({state_new,steps+1});
                }
            } else if( c1 == 0 ) {
                // swap c1 c0
                state_new = c1 + (c0<<3) + (c2<<6) + (c3<<9) + (c4<<12) + (c5<<15);
                if( !seen[state_new] ) {
                    seen[state_new] = 1;
                    q.push({state_new,steps+1});
                }
                // swap c1 c4
                state_new = c0 + (c4<<3) + (c2<<6) + (c3<<9) + (c1<<12) + (c5<<15);
                if( !seen[state_new] ) {
                    seen[state_new] = 1;
                    q.push({state_new,steps+1});
                }
                // swap c1 c2
                state_new = c0 + (c2<<3) + (c1<<6) + (c3<<9) + (c4<<12) + (c5<<15);
                if( !seen[state_new] ) {
                    seen[state_new] = 1;
                    q.push({state_new,steps+1});
                }
            } else if( c2 == 0 ) {
                // swap c2 c1
                state_new = c0 + (c2<<3) + (c1<<6) + (c3<<9) + (c4<<12) + (c5<<15);
                if( !seen[state_new] ) {
                    seen[state_new] = 1;
                    q.push({state_new,steps+1});
                }
                // swap c2 c5
                state_new = c0 + (c1<<3) + (c5<<6) + (c3<<9) + (c4<<12) + (c2<<15);
                if( !seen[state_new] ) {
                    seen[state_new] = 1;
                    q.push({state_new,steps+1});
                }
            } else if( c3 == 0 ) {
                // swap c3 c0
                state_new = c3 + (c1<<3) + (c2<<6) + (c0<<9) + (c4<<12) + (c5<<15);
                if( !seen[state_new] ) {
                    seen[state_new] = 1;
                    q.push({state_new,steps+1});
                }
                // swap c3 c4
                state_new = c0 + (c1<<3) + (c2<<6) + (c4<<9) + (c3<<12) + (c5<<15);
                if( !seen[state_new] ) {
                    seen[state_new] = 1;
                    q.push({state_new,steps+1});
                }
            } else if( c4 == 0 ) {
                // swap c4 c3
                state_new = c0 + (c1<<3) + (c2<<6) + (c4<<9) + (c3<<12) + (c5<<15);
                if( !seen[state_new] ) {
                    seen[state_new] = 1;
                    q.push({state_new,steps+1});
                }
                // swap c4 c1
                state_new = c0 + (c4<<3) + (c2<<6) + (c3<<9) + (c1<<12) + (c5<<15);
                if( !seen[state_new] ) {
                    seen[state_new] = 1;
                    q.push({state_new,steps+1});
                }
                // swap c4 c5
                state_new = c0 + (c1<<3) + (c2<<6) + (c3<<9) + (c5<<12) + (c4<<15);
                if( !seen[state_new] ) {
                    seen[state_new] = 1;
                    q.push({state_new,steps+1});
                }
            } else {
                // swap c5 c4
                state_new = c0 + (c1<<3) + (c2<<6) + (c3<<9) + (c5<<12) + (c4<<15);
                if( !seen[state_new] ) {
                    seen[state_new] = 1;
                    q.push({state_new,steps+1});
                }
                // swap c5 c2
                state_new = c0 + (c1<<3) + (c5<<6) + (c3<<9) + (c4<<12) + (c2<<15);
                if( !seen[state_new] ) {
                    seen[state_new] = 1;
                    q.push({state_new,steps+1});
                }
            }
        }

        return -1;
    }
};
