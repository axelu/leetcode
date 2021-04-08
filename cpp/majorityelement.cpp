


// Majority Element
// https://leetcode.com/problems/majority-element/


class Solution {
public:
    int majorityElement(vector<int>& nums) {
        if( nums.size() == 1 ) return nums[0];
        if( nums.size() == 2 && nums[0] == nums[1] ) return nums[0];

        unordered_map<int,int> t;
        for(auto i : nums) {
            auto p = t.insert({i,1});
            if( !p.second ) {
                if( p.first->second + 1 > nums.size()/2 ) {
                    return i;
                } else {
                    p.first->second += 1;
                }
            }
        }
        return 0; // should never get here
    }
};
