
// 945. Minimum Increment to Make Array Unique
// https://leetcode.com/problems/minimum-increment-to-make-array-unique/



class Solution {
public:
    int minIncrementForUnique(vector<int>& nums) {
        int n = nums.size();

        map<int,int> cnt; // integer,count

        for(int x: nums)
            ++cnt[x];

        int ans = 0;

        auto it = cnt.begin();
        while( it != cnt.end() ) {
            if( it->second == 1 ) {
                ++it;
                continue;
            }

            // we need to increase all but one of the integers
            ans += it->second - 1;

            auto p = cnt.insert({it->first + 1, it->second - 1});
            if( !p.second )
                p.first->second = p.first->second + (it->second - 1);
            it = p.first;
        }

        return ans;
    }
};
