
// 1536. Minimum Swaps to Arrange a Binary Grid
// https://leetcode.com/problems/minimum-swaps-to-arrange-a-binary-grid/




class Solution {
public:
    int minSwaps(vector<vector<int>>& grid) {
        int n = grid.size();

        deque<pair<int,int>> dq; // row (0-indexed), rightmost 1

        for(int i = 0; i < n; ++i) {
            int last = -1;
            for(int j = 0; j < n; ++j)
                if( grid[i][j] == 1 )
                    last = j;

            dq.push_front({i,last});
        }

        int swaps = 0;

        for(int i = 0; i < n-1; ++i) {

            // get the next possible row meeting our criteria
            // criteria: last <= i

            stack<pair<int,int>> parking_lot;
            while( !dq.empty() && dq.back().second > i ) {
                // park the current row
                parking_lot.push(dq.back());
                dq.pop_back();
            }

            if( dq.empty() )
                return -1;

            swaps += parking_lot.size();
            dq.pop_back();

            while( !parking_lot.empty() ) {
                auto p = parking_lot.top();
                parking_lot.pop();
                ++p.first;
                dq.push_back(p);
            }
        }

        return swaps;
    }
};
