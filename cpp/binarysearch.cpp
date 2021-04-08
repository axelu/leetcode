
// Binary Search
// day 8 October 2020 challenge
// https://leetcode.com/explore/challenge/card/october-leetcoding-challenge/560/week-2-october-8th-october-14th/3488/
// https://leetcode.com/problems/binary-search/



class Solution {
public:
    int search(vector<int>& nums, int target) {
        auto n = nums.size();
        if( n == 0 ) return -1;
        if( n == 1 && nums[0] != target ) return -1;
        if( target < nums[0] || target > nums.back() ) return -1;

        int i = 0;
        for(; i < n; ++i) {
            if( nums[i] == target ) break;
        }
        return i == n ? -1: i;
    }
};
