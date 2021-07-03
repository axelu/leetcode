
// 1696. Jump Game VI
// https://leetcode.com/problems/jump-game-vi/
// day 9 June 2021 challenge
// https://leetcode.com/explore/challenge/card/june-leetcoding-challenge-2021/604/week-2-june-8th-june-14th/3773/





class Solution {
public:
    int maxResult(vector<int>& nums, int k) {
        int n = nums.size();
        if( n < 3 || k == 1 )
            return accumulate(begin(nums),end(nums),0);

        // max heap
        auto cmp = [](const array<int,2>& a, const array<int,2>& b){
            if( a[0] < b[0] ) {
                return true;
            } else if( a[0] == b[0] ) {
                if( a[1] < b[1] )
                    return true;
            }
            return false;
        };
        priority_queue<array<int,2>,vector<array<int,2>>,decltype(cmp)> pq(cmp);

        pq.push({nums[n-1],n-1});
        pq.push({nums[n-2]+nums[n-1],n-2});

        int ans = 0;
        // bottom up DP
        for(int i = n-3; i >= 0; --i) {
            while( pq.top()[1] > i+k )
                pq.pop();
            ans = nums[i]+pq.top()[0];
            pq.push({ans,i});
        }
        return ans;
    }
};
