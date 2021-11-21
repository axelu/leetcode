
// 1997. First Day Where You Have Been in All the Rooms
// https://leetcode.com/problems/first-day-where-you-have-been-in-all-the-rooms/



// good explanation
// https://leetcode.com/problems/first-day-where-you-have-been-in-all-the-rooms/discuss/1459388/Understanding-the-Logic.

class Solution {
public:
    int firstDayBeenInAllRooms(vector<int>& nextVisit) {
        int n = nextVisit.size(); // 2 <= n <= 10^5

        long mod = 1000000007;

        long dp[n]; // number of days when we reach room i the first time
        dp[0] = 0;
        for(int i = 1; i < n; ++i)
            dp[i] = (dp[i-1] * 2 - dp[nextVisit[i-1]] + 2 + mod) % mod;

        return dp[n- 1];
    }
};
