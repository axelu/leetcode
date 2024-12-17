
// 3276. Select Cells in Grid With Maximum Score
// https://leetcode.com/problems/select-cells-in-grid-with-maximum-score/




class Solution {
private:
    map<int,unordered_set<int>> mp;

    // mem[val][state]
    // 1 <= val <= 100
    // state: we have 10 rows max, using a bitmask, binary 1111111111 = descimal 1023
    int mem[101][1024];


    int rec(map<int,unordered_set<int>>::reverse_iterator it, int state) {
        if( it == mp.rend() )
            return 0;

        int val = it->first; // 1 <= val <= 100

        if( mem[val][state] != -1 )
            return mem[val][state];

        // we have a choice
        //     don't take the value OR
        //     take the value if we can aka if a row in which the value exist is still not taken

        int res = rec(next(it), state);

        for(auto it_row = it->second.begin(); it_row != it->second.end(); ++ it_row) {
            int row = *it_row;
            if( state & (1<<row) )
                continue;

            int state_new = state | (1<<row);
            res = max(res, val + rec(next(it), state_new));
        }

        return mem[val][state] = res;
    }


public:
    int maxScore(vector<vector<int>>& grid) {
        int n = grid.size();    // rows
        int m = grid[0].size(); // cols

        // if we greedily pick the largest value from each row
        // we could end up picking dup values, which is not allowed
        // we would pick the value from the row, where another row has the next largest value bigger or equal
        // example
        //     20,10
        //     20,11
        // we would pick 20 from the 1st row and 11 from the second row, but this cascades
        // example
        //     20,10
        //     20,11,5
        //        11,6
        // what if we extract all unique values from the grid and for each the rows that they exists
        // worst case is 100 unique values each existing 1s, or
        // 1 unique value existing 100 times, but we could only pick it one time due to constraint
        // exmaple grid
        //     4 4 4
        //     4 4 4
        //     4 4 4
        //     answer is 4 as we only can pick unique values


        for(int i = 0; i < n; ++i) { // row
            for(int j = 0; j < m; ++j) { // col
                mp[grid[i][j]].insert(i);
            }
        }

        memset(mem,-1,sizeof mem);
        return rec(mp.rbegin(), 0);
    }
};
