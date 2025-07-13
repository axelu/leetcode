
// 3595. Once Twice
// https://leetcode.com/problems/once-twice/






class Solution {
public:
    vector<int> onceTwice(vector<int>& nums) {
        unordered_map<int,int> cnt;
        for(int x: nums) {
            ++cnt[x];
            if( cnt[x] == 3 )
                cnt.erase(x);
        }

        vector<int> ans(2);
        ans[0] = cnt.begin()->second == 1 ? cnt.begin()->first : next(cnt.begin())->first;
        ans[1] = cnt.begin()->second == 2 ? cnt.begin()->first : next(cnt.begin())->first;

        return ans;
    }
};
