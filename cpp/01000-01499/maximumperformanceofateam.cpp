
// 1383. Maximum Performance of a Team
// https://leetcode.com/problems/maximum-performance-of-a-team/
// day 5 June 2021 challenge
// https://leetcode.com/explore/challenge/card/june-leetcoding-challenge-2021/603/week-1-june-1st-june-7th/3768/



class Solution {
public:
    int maxPerformance(int n, vector<int>& speed, vector<int>& efficiency, int k) {
        long MOD = 1e9+7;

        if( n == 1 ) return ((long)efficiency[0]*(long)speed[0])%MOD;

        int i;

        vector<vector<long>> v(n,vector<long>(2));  // efficiency,speed
        for(i = 0; i < n; ++i)
            v[i] = {efficiency[i],speed[i]};
        // sort engineers by efficiency decreasing
        // if same efficiency sort by decreasing speed
        sort(v.begin(),v.end(),[](const vector<long>& a, const vector<long>& b){
            if( a[0] > b[0] )
                return true;
            else if( a[0] == b[0] )
                if( a[1] > b[1] )
                    return true;
            return false;
        });


        // min speed priority queue / heap
        priority_queue<long,vector<long>,greater<long>> pq;

        long ans = 0;
        long speedSum = 0;
        for(i = 0; i < n; ++i) {
            if( i >= k ) {
                // as we can only have k engineers, we
                // "replace" the slowest speed engineer
                speedSum -= pq.top(); // get speed of the slowest engineer
                pq.pop();             // remove the slowest engineer
            }

            speedSum += v[i][1];

            // does adding the current engineer give us a better result?
            ans = max(ans, speedSum * v[i][0]);

            pq.push(v[i][1]); // add speed of our current engineer to minspeed heap
        }

        return ans % MOD;
    }
};
