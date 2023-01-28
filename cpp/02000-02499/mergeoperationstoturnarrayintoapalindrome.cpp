
// 2422. Merge Operations to Turn Array Into a Palindrome
// https://leetcode.com/problems/merge-operations-to-turn-array-into-a-palindrome/




class Solution {
public:
    int minimumOperations(vector<int>& nums) {
        int n = nums.size();

        int ans = 0;

        int i = 0;
        long carry_i = 0;
        int j = n-1;
        long carry_j = 0;
        while( i < j ) {
           // if nums[i] != nums[j] we have no other choice
            //   than to merge the smaller of the two with its adjacent element

            if( nums[i] + carry_i== nums[j] + carry_j ) {
                ++i;
                carry_i = 0;
                --j;
                carry_j = 0;
            } else if( nums[i] + carry_i < nums[j] + carry_j ) {
                carry_i += nums[i];
                ++i;
                ++ans;
            } else { // nums[i] + carry_i > nums[j] + carry_j
                carry_j += nums[j];
                --j;
                ++ans;
            }
        }

        return ans;
    }
};
