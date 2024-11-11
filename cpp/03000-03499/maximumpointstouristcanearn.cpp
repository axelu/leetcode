
// 3332. Maximum Points Tourist Can Earn
// https://leetcode.com/problems/maximum-points-tourist-can-earn/




class Solution {
public:
    int maxScore(int n, int k, vector<vector<int>>& stayScore, vector<vector<int>>& travelScore) {

        int _pre[n]; int * pre = _pre;
        int _cur[n]; int * cur = _cur;

        // it is day 0
        for(int city = 0; city < n; ++city) {
            // we can choose any city as our starting point
            // so we could have stay on day 0 in our 'starting city' OR
            // day 0 is a travel day to our city from any other city

            // arrive from any other city
            int a = 0;
            for(int j = 0; j < n; ++j)
                a = max(a, travelScore[j][city]);
            // stayed
            a = max(a, stayScore[0][city]);

            pre[city] = a;
        }

        for(int day = 1; day < k; ++day) {

            for(int city = 0; city < n; ++city) {
                int a = 0;
                // arrive from any other city
                for(int j = 0; j < n; ++j) {
                    a = max(a, pre[j] + travelScore[j][city]);
                }
                // stayed
                a = max(a, pre[city] + stayScore[day][city]);

                cur[city] = a;
            }

            // swap
            int * t = pre;
            pre = cur;
            cur = t;
        }

        int ans = 0;
        for(int city = 0; city < n; ++city)
            ans = max(ans, pre[city]);

        return ans;
    }
};
