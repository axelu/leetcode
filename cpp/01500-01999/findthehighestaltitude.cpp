
// 1732. Find the Highest Altitude
// https://leetcode.com/problems/find-the-highest-altitude/


class Solution {
public:
    int largestAltitude(vector<int>& gain) {
        int n = gain.size();

        int ans = 0;  // starting altitude
        int alt = 0;  // running altitude
        for(int i = 0; i < n; ++i) {
            alt += gain[i];
            ans = max(ans,alt);
        }
        return ans;
    }
};
