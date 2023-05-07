
// 2568. Minimum Impossible OR
// https://leetcode.com/problems/minimum-impossible-or/



class Solution {
public:
    int minImpossibleOR(vector<int>& nums) {
        // any integer in nums is NOT the answer
        // any integer that is not a power of 2
        //    is a composition of power of 2 integers
        // so really, the smallest power of 2 not in nums
        // is the answer

        sort(nums.begin(),nums.end());
        int p2 = 1;

        for(int x: nums)
            if( x == p2 )
                p2 *= 2;
            else if( x > p2 )
                break;

        return p2;
    }
};
