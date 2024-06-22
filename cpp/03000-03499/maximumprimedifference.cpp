
// 3115. Maximum Prime Difference
// https://leetcode.com/problems/maximum-prime-difference/





// 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97
//                              0     1      2     3    4     5     6     7     8     9
bool primes_below_101[101] = {false,false, true, true,false, true,false, true,false,false
                             ,false, true,false, true,false,false,false, true,false, true
                             ,false,false,false, true,false,false,false,false,false, true
                             ,false, true,false,false,false,false,false, true,false,false
                             ,false, true,false, true,false,false,false, true,false,false
                             ,false,false,false, true,false,false,false,false,false, true
                             ,false, true,false,false,false,false,false, true,false,false
                             ,false, true,false, true,false,false,false,false,false, true
                             ,false,false,false, true,false,false,false,false,false, true
                             ,false,false,false,false,false,false,false, true,false,false
                             ,false};

class Solution {
public:
    int maximumPrimeDifference(vector<int>& nums) {
        int n = nums.size();
        // it is guaranteed, that nums has at least on prime number

        int i = 0;
        for(; i < n; ++i)
            if( primes_below_101[nums[i]] )
                break;

        if( i == n-1 )
            return 0;

        int j = n-1;
        for(; j >= 0; --j)
            if( primes_below_101[nums[j]] )
                break;

        return j-i;
    }
};
