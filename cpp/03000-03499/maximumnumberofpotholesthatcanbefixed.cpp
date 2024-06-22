
// 3119. Maximum Number of Potholes That Can Be Fixed
// https://leetcode.com/problems/maximum-number-of-potholes-that-can-be-fixed/





class Solution {
public:
    int maxPotholes(string road, int budget) {
        int n = road.size();

        priority_queue<int> pq;
        int cnt = 0;
        for(int i = 0; i < n; ++i) {
            if( road[i] == '.' ) {
                if( cnt > 0 ) {
                    pq.push(cnt);
                    cnt = 0;
                }
            } else {
                ++cnt;
            }
        }
        // finish up
        if( cnt > 0 )
            pq.push(cnt);


        int ans = 0;
        while( !pq.empty() && budget > 1 ) {
            int consecutive_potholes = pq.top();
            pq.pop();

            if( consecutive_potholes + 1 <= budget ) {
                ans += consecutive_potholes;
                budget -= consecutive_potholes + 1;

            } else {
                int consecutive_potholes_rem =  consecutive_potholes - (budget - 1);
                pq.push(consecutive_potholes_rem);
                ans += budget - 1;
                budget = 0;
            }
        }

        return ans;
    }
};
