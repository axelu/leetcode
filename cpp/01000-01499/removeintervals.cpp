
// 1272. Remove Interval
// https://leetcode.com/problems/remove-interval/



class Solution {
public:
    vector<vector<int>> removeInterval(vector<vector<int>>& intervals, vector<int>& toBeRemoved) {
        int n = intervals.size();

        vector<vector<int>> ans;
        int s = toBeRemoved[0];
        int e = toBeRemoved[1];

        for(int i = 0; i < n; ++i) {
            int a = intervals[i][0];
            int b = intervals[i][1];

            if( b <= s ) {
                ans.push_back({a,b});

            } else if( b > s && b <= e ) {
                if( a < s ) {
                    ans.push_back({a,s});
                }

            } else { // b > e
                if( a < s ) {
                    ans.push_back({a,s});
                    ans.push_back({e,b});
                } else if( a >= s && a <= e ) {
                    ans.push_back({e,b});
                } else {
                    ans.push_back({a,b});
                }
            }
        }

        return ans;
    }
};
