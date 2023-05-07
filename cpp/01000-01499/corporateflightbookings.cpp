
// 1109. Corporate Flight Bookings
// https://leetcode.com/problems/corporate-flight-bookings/



class Solution {
public:
    vector<int> corpFlightBookings(vector<vector<int>>& bookings, int n) {
        vector<int> ans(n+1,0);

        for(auto& v: bookings) {
            // v[0] first inclusive
            // v[1] last inclusive
            // v[2] seats

            ans[v[0]-1] += v[2];
            ans[v[1]] -= v[2];
        }

        for(int i = 1; i < n; ++i)
            ans[i] += ans[i-1];

        ans.pop_back();

        return ans;
    }
};
