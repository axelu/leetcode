
// 3219. Minimum Cost for Cutting Cake II
// https://leetcode.com/problems/minimum-cost-for-cutting-cake-ii/


class Solution {
public:
    long long minimumCost(int m, int n, vector<int>& horizontalCut, vector<int>& verticalCut) {

        priority_queue<array<int,2>> pq; // cost, 0 horizontal, 1 vertical
        for(int c: horizontalCut)
            pq.push({c,0});
        for(int c: verticalCut)
            pq.push({c,1});

        long long h_cuts = 0;
        long long v_cuts = 0;
        long long ans = 0LL;
        while( !pq.empty() ) {
            long long cost = pq.top()[0];
            int cut = pq.top()[1];
            pq.pop();

            if( cut == 0 ) {
                ans += (v_cuts + 1LL) * cost;
                ++h_cuts;
            } else {
                ans += (h_cuts + 1LL) * cost;
                ++v_cuts;
            }
        }

        return ans;
    }
};
