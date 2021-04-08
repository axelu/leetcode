
// 84. Largest Rectangle in Histogram
// https://leetcode.com/problems/largest-rectangle-in-histogram/
// day 31 December 2020 challenge
// https://leetcode.com/explore/challenge/card/december-leetcoding-challenge/573/week-5-december-29th-december-31st/3587/

class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        int n = heights.size();
        if( n == 0 ) return 0;
        if( n == 1 ) return heights[0];

        int ans = 0, idx;
        priority_queue<array<int,2>> q;
        array<int,2> qe;
        for(int i = 0; i < n; ++i) {
            if( q.empty() ) {
                q.push({heights[i],i});
                continue;
            }
            idx = -1;
            while( !q.empty() ) {
                qe = q.top();
                if( qe[0] == heights[i] ) {
                    idx = -1;
                    break;
                } else if( qe[0] < heights[i] ) {
                    if( idx == -1 ) idx = i;
                    break;
                } else {
                    // qe[0] > heights[i]
                    idx = qe[1];
                    ans = max(ans,qe[0]*(i-qe[1]));
                    q.pop();
                }
            }
            if( idx != -1 )
                q.push({heights[i],idx});
        }
        // finish up
        while( !q.empty() ) {
            qe = q.top();
            q.pop();
            ans = max(ans,qe[0]*(n-qe[1]));
        }

        return ans;
    }
};
