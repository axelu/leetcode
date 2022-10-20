
// 659. Split Array into Consecutive Subsequences
// https://leetcode.com/problems/split-array-into-consecutive-subsequences/




class Solution {
public:
    bool isPossible(vector<int>& nums) {
        // greedy:
        //   if we can add nums[i] to an existing subsequence,
        //   then we want to add it to the shortest one

        priority_queue<int,vector<int>,greater<int>> pqs[2001];

        for(auto x: nums) {
            x += 1000;
            if( x-1 > 0 && !pqs[x-1].empty() ) {
                pqs[x].push(pqs[x-1].top()+1);
                pqs[x-1].pop();
            } else
                pqs[x].push(1);
        }

        for(int i = 0; i < 2001; ++i)
            if( !pqs[i].empty() && pqs[i].top() < 3 )
                return false;

        return true;
    }
};
