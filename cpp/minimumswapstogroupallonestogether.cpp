
// 1151. Minimum Swaps to Group All 1's Together
// https://leetcode.com/problems/minimum-swaps-to-group-all-1s-together/
// day 15 April 2021 challenge
// https://leetcode.com/explore/challenge/card/april-leetcoding-challenge-2021/595/week-3-april-15th-april-21st/3708/




class Solution {
public:
    int minSwaps(vector<int>& data) {
        int n = data.size();

        // count the ones in the data
        int ones = 0;
        int i;
        for(i = 0; i < n; ++i)
            if( data[i] == 1 ) ++ones;
        // cout << ones << endl;
        if( ones <= 1 ) return 0;
        if( ones == n ) return 0;

        // move a sliding window of size ones accross data
        // count the number of zeros in each window
        // the minimum number of zeros encountered in all windows of size ones
        // is the answer
        int ans;
        int zeros = 0;
        int j = 0;
        for(i = 0; i < n; ++i) {
            if( data[i] == 0 ) ++zeros;
            if( i == ones-1 ) ans = zeros;
            if( i > ones-1 ) {
                if( data[j] == 0 ) --zeros;
                ans = min(ans,zeros);
                ++j;
            }
        }

        return ans;
    }
};
