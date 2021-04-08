
// 594. Longest Harmonious Subsequence
// https://leetcode.com/problems/longest-harmonious-subsequence/
// day 4 February 2021 challenge
// https://leetcode.com/explore/featured/card/february-leetcoding-challenge-2021/584/week-1-february-1st-february-7th/3628/



class Solution {
public:
    int findLHS(vector<int>& nums) {
        size_t n = nums.size();
        if( n < 2 ) return 0;

        int ans = 0;
        map<int,int> m;
        pair<map<int,int>::iterator,bool> p;
        for(int i = 0; i < n; ++i) {
            p = m.insert({nums[i],1});
            if( !p.second ) ++p.first->second;
        }
        if( m.size() == 1 ) return 0;
        int prv,cur,cntPrv,cntCur;
        for(auto it = next(m.begin()); it != m.end(); ++it) {
            prv = prev(it)->first;
            cur = it->first;
            if( cur - prv == 1 ) {
                cntPrv = prev(it)->second;
                cntCur = it->second;
                ans = max(ans,cntPrv+cntCur);
            }
        }

        return ans;
    }
};
