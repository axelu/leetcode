
// 3190. Find Minimum Operations to Make All Elements Divisible by Three
// https://leetcode.com/problems/find-minimum-operations-to-make-all-elements-divisible-by-three/



class Solution {
public:
    int minimumOperations(vector<int>& nums) {
        int ans = 0;
        for(int x: nums)
            if( x % 3 )
                ++ans;
        return ans;
    }
};
