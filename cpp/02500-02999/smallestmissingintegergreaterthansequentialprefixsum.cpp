

// 2996. Smallest Missing Integer Greater Than Sequential Prefix Sum
// https://leetcode.com/problems/smallest-missing-integer-greater-than-sequential-prefix-sum/



class Solution {
public:
    int missingInteger(vector<int>& nums) {
        auto it = nums.begin();
        if( nums.size() == 1 )
            return *it + 1;

        int sum = *it;
        ++it;
        for( ; it != nums.end(); ++it) {
            if( *it != *prev(it) +1 )
                break;
            sum += *it;
        }

        sort(it,nums.end());
        --it;
        for( ; it != nums.end(); ++it) {
            if( *it < sum )
                continue;
            else if( *it == sum )
                ++sum;
            else
                break;
        }

        return sum;
    }
};
