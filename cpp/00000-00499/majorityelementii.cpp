
// day 22 September 2020 challenge
// 229. Majority Element II
// https://leetcode.com/explore/challenge/card/september-leetcoding-challenge/557/week-4-september-22nd-september-28th/3469/
// https://leetcode.com/problems/majority-element-ii/


class Solution {
public:
    vector<int> majorityElement(vector<int>& nums) {
        if( nums.empty() ) return {};

        int n = nums.size() / 3;

        unordered_map<int,int> m;
        vector<int> r;
        for(int i : nums) {
            auto p = m.insert({i,1});
            if( !p.second ) {
                if( p.first->second < 0 ) continue;
                ++p.first->second;
                if( p.first->second > n ) {
                    r.push_back(i);
                    p.first->second = -1;
                }
            } else {
                if( n == 0 ) {
                    // single entry already exceeds majority
                    r.push_back(i);
                    p.first->second = -1;
                }
            }
        }

        return r;
    }
};
