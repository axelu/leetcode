
// 3386. Button with Longest Push Time
// https://leetcode.com/problems/button-with-longest-push-time/




class Solution {
public:
    int buttonWithLongestTime(vector<vector<int>>& events) {
        int n = events.size();
        if( n == 1 )
            return events[0][0];

        int ans_d = events[0][1];
        int ans_b = events[0][0];

        for(int i = 1; i < n; ++i) {
            int button = events[i][0];
            int t = events[i][1];

            int d = t - events[i-1][1];
            if( d > ans_d ) {
                ans_d = d;
                ans_b = button;
            } else if( d == ans_d ) {
                if( button < ans_b )
                    ans_b = button;
            }

        }

        return ans_b;
    }
};
