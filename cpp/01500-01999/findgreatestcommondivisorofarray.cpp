
// 1979. Find Greatest Common Divisor of Array
// https://leetcode.com/problems/find-greatest-common-divisor-of-array/





class Solution {
private:
    // recursive function to return gcd of a and b
    long long gcd(long long int a, long long int b) {
        if( b == 0 )
            return a;
        return gcd(b,a % b);
    }



public:
    int findGCD(vector<int>& nums) {

        const auto [mn,mx] = minmax_element(begin(nums),end(nums));
        return gcd(*mn,*mx);
    }
};
