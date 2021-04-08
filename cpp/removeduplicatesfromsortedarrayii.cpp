
// 80. Remove Duplicates from Sorted Array II
// https://leetcode.com/problems/remove-duplicates-from-sorted-array-ii/
// day 11 December 2020 challenge
// https://leetcode.com/explore/challenge/card/december-leetcoding-challenge/570/week-2-december-8th-december-14th/3562/




class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        size_t n = nums.size();
        if( n <= 2 )
            return n;
        if( n == 3 )
            return nums[0] == nums[1] && nums[1] == nums[2] ? 2 : 3;

        int cnt = 1;
        int cur = nums[1];
        if( nums[0] == cur )
            ++cnt;

        auto wit = nums.begin() + 2;
        for(auto rit = nums.begin() + 2; rit != nums.end(); ++rit) {
            if( *rit != cur ) {
                cur = *rit;
                cnt = 1;
                if( wit != rit ) *wit = *rit;
                ++wit;
            } else {
                ++cnt;
                if( cnt == 2 ) {
                    if( wit != rit ) *wit = *rit;
                    ++wit;
                }
            }
        }
        // cout << wit - nums.begin() << endl;
        return wit - nums.begin();
    }
};
