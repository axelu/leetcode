
// Special Array With X Elements Greater Than or Equal X
// https://leetcode.com/contest/weekly-contest-209/problems/special-array-with-x-elements-greater-than-or-equal-x/
// https://leetcode.com/problems/special-array-with-x-elements-greater-than-or-equal-x/



class Solution {
public:
    int specialArray(vector<int>& nums) {
        auto n = nums.size();
        if( n == 1 && nums[0] > 1 ) return 1;

        map<int,int> m;
        for(int i = 0; i < n; ++i) {
            auto p = m.insert({nums[i],1});
            if( !p.second )
                ++p.first->second;
        }

        auto ite = m.end();
        for(int x = 0; x <= n; ++x) {
            auto it = m.lower_bound(x);
            if( it == ite ) {
                continue;
            } else {
                int k = 0;
                for(; it != ite; ++it )
                    k += it->second;
                if( x == k ) return x;
            }
        }

        return -1;
    }
};
