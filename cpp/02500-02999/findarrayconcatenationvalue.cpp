
// 2562. Find the Array Concatenation Value
// https://leetcode.com/problems/find-the-array-concatenation-value/




class Solution {
public:
    long long findTheArrayConcVal(vector<int>& nums) {
        int n = nums.size();

        long long ans = 0LL;

        int i = 0;
        int j = n-1;

        while( i <= j ) {

            if( i == j ) {
                ans += nums[i];
                break;
            }

            string s1 = to_string(nums[i]);
            string s2 = to_string(nums[j]);
            string s = s1 + s2;
            long long t = stoll(s);
            ans += t;

            ++i;
            --j;
        }

        return ans;
    }
};
