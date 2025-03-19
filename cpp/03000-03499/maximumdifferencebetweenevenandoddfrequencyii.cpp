
// 3445. Maximum Difference Between Even and Odd Frequency II
// https://leetcode.com/problems/maximum-difference-between-even-and-odd-frequency-ii/






class Solution {
private:
    const int INF = 100000;

    int get_state(int freq_a, int freq_b) {
        int state = 0;
        // freq_a bit 1
        state |= ((freq_a % 2) << 1);
        // freq_b bit 0
        state |= (freq_b % 2);

        return state;
    }

    int solve(vector<vector<int>>& prefixSum, int n, int a, int b, int k) {
        // a char with odd freq
        // b char with even freq

        // we can have 4 states
        // state | freq[a]  | freq[b]
        // 0       even       even
        // 1       even       odd
        // 2       odd        even
        // 3       odd        odd

        // we need to pair only valid states of begin window and end window
        //         i       j
        // . . . . . . . . . . . . . . . . . . .
        // Note: both char a and char b must be in window
        // Note: begin window refers to count up to and including pos i-1 !!! because prefixSum
        //       but because of prefixSum freq[c][i] and freq[c][j+1]
        //     begin window i              end window j             in window
        //     freq[a] freq[b] state       freq[a] freq[b] state    freq[a] freq[b] state
        //     even    even    0           even    even    0        even    even    0        invalid
        //     even    even    0           even    odd     1        even    odd     1        invalid
        //     even    even    0           odd     even    2        odd     even    2        VALID
        //     even    even    0           odd     odd     3        odd     odd     3        invalid
        //     even    odd     1           even    even    0        even    odd     1        invalid
        //     even    odd     1           even    odd     1        even    even    0        invalid
        //     even    odd     1           odd     even    2        odd     odd     3        invalid
        //     even    odd     1           odd     odd     3        odd     even    2        VALID
        //     odd     even    2           even    even    0        odd     even    2        VALID
        //     odd     even    2           even    odd     1        odd     odd     3        invalid
        //     odd     even    2           odd     even    2        even    even    0        invalid
        //     odd     even    2           odd     odd     3        even    odd     1        invalid
        //     odd     odd     3           even    even    0        odd     odd     3        invalid
        //     odd     odd     3           even    odd     1        odd     even    2        VALID
        //     odd     odd     3           odd     even    2        even    odd     1        invalid
        //     odd     odd     3           odd     odd     3        even    even    0        invalid

        // let us calculate freq[a] - freq[b] at each index
        // and carry forward the minimum for each state seen up to that index
        vector<vector<int>> mndiff(4,vector<int>(n, INF));
        for(int i = 0; i < n; ++i) {
            int freq_a = prefixSum[a][i+1];
            int freq_b = prefixSum[b][i+1];
            int diff = freq_a - freq_b;
            int state = get_state(freq_a, freq_b);
            if( i == 0 ) {
                mndiff[state][0] = diff;
            } else {
                for(int j = 0; j < 4; ++j) {
                    if( j == state ) {
                        mndiff[j][i] = min(mndiff[j][i-1], diff);
                    } else {
                        mndiff[j][i] = mndiff[j][i-1];
                    }
                }
            }
        }

        int ret = INT_MIN;

        // sliding window
        // i left index of window
        // j right index of window
        // length of window j - i + 1 has to be greater equal k
        // we have to have both char a and char b in the window
        //     x   i      j
        // . . . . . . . . . . . . . . . . . . .
        // our best solution though can lie on an index 0 <= x <= i

        int i = 0;                             // left index
        for(int j = max(2, k-1); j < n; ++j) { // right index
            int freq_a_j = prefixSum[a][j+1];
            int freq_b_j = prefixSum[b][j+1];
            if( freq_a_j == 0 || freq_b_j == 0 )
                continue;

            int state_j = get_state(freq_a_j, freq_b_j);

            int freq_a_i = prefixSum[a][i];
            int freq_b_i = prefixSum[b][i];

            int freq_a_window = freq_a_j - freq_a_i;
            int freq_b_window = freq_b_j - freq_b_i;

            // also need to check the entire window from 0
            if( state_j == 2 )
                ret = max(ret, freq_a_j - freq_b_j);

            // what is the state at i we are looking for based on state at j?
            // state   i    j
            //         2    0
            //         3    1
            //         0    2
            //         1    3
            int state_i = (state_j + 2) % 4;

            while( j - i + 1 >= max(3, k) && freq_a_i < freq_a_j && freq_b_i < freq_b_j ) {

                // if( i == 0 ) {
                    // state at j has to be 2
                //     if( state_j == 2 )
                //         ret = max(ret, freq_a_j - freq_b_j); // should be our first time, so don't need max really

                // } else {
                // if( i > 0 ) {
                //     // also need to check the entire window from 0
                //     // if( state_j == 2 )
                    //     ret = max(ret, freq_a_j - freq_b_j);
                //    int state_i = (state_j + 2) % 4;
                //    ret = max(ret, (freq_a_j - freq_b_j) - mndiff[state_i][i-1]);
                // }

                ++i;
                freq_a_i = prefixSum[a][i];
                freq_b_i = prefixSum[b][i];
                freq_a_window = freq_a_j - freq_a_i;
                freq_b_window = freq_b_j - freq_b_i;
            }
            if( i > 1 )
                ret = max(ret, (freq_a_j - freq_b_j) - mndiff[state_i][i-2]);

        }

        return ret;
    }

public:
    int maxDifference(string s, int k) {
        int n = s.size(); // 3 <= s.length <= 3 * 1e4
        // s consists only of digits '0' to '4'

        // max difference = frequency character with an odd frequency minus
        //                  frequency of character with an even frequency

        // find a string that is at least k long
        // that has the largest amount of odd char a and at least 2 chars b
        // example s = "333232322"; k = 8
        //              ---------
        //         => ans = 1, we cannot just use "3332323"
        //         which would yield ans = 3
        //         ( odd: 3s, 5 of them, even 2s, 2 of them, odd - even  = 5 - 2 = 3 )
        //         because is only 7 long, but k = 8, hence needs to be longer than 7
        // example s = "333232322"; k = 7 => ans = 3
        // example s = "333232312"; k = 8 => ans = 3

        // idea:
        // we have only 5 chars (0,1,2,3,4), we can dedicate one as odd and the other as even
        // that gives us 5 x 4 possibilities
        // from the problem description:
        //    maximize freq[a] - freq[b], where freq[a] is odd and freq[b] is even
        // sliding window
        // for the odd one:  freq on right end | freq on left start | freq in window
        //                      odd                   even              odd
        //                      even                  odd               odd
        // for the even one: freq on right end | freq on left start | freq in window
        //                      odd                   odd               even
        //                      even                  even              even
        // our window cannot be shorter than k and must include char a and b
        // meaning neither freq of a nore freq of b in window can be 0

        vector<vector<int>> prefixSum(5, vector<int>(n+1, 0));
        for(int i = 1; i <= n; ++i) {
            for(int c = 0; c < 5; ++ c) {
                if( s[i-1]-'0' == c )
                    prefixSum[c][i] = prefixSum[c][i-1] + 1;
                else
                    prefixSum[c][i] = prefixSum[c][i-1];
            }
        }

        // int tt1 = solve(prefixSum, n, 0, 4, k);
        // return tt1;

        int ans = INT_MIN;

        for(int a = 0; a < 5; ++a) {        // odd freq char
            if( prefixSum[a][n] == 0 )
                continue;
            for(int b = 0; b < 5; ++b) {    // even freq char
                if( a == b )
                    continue;
                if( prefixSum[b][n] == 0 )
                    continue;

                int t = solve(prefixSum, n, a, b, k);
                ans = max(ans, t);
            }
        }

        return ans;
    }
};
