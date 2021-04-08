
// Contains Duplicate II
// https://leetcode.com/problems/contains-duplicate-ii/


class Solution {
public:
    bool containsNearbyDuplicate(vector<int>& nums, int k) {
        if( nums.empty() || nums.size() == 1) return false;

        size_t ns = nums.size();
        unordered_map<int,int> m;
        for(auto i = 0; i < ns; ++i) {
            auto p = m.insert({nums[i],i});
            if( !p.second ) {
                if ( i - p.first->second <= k ) return true;
                p.first->second = i;
            }
        }

        return false;
    }
};
