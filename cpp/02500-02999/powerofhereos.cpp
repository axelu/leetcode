
// 2681. Power of Heroes
// https://leetcode.com/problems/power-of-heroes/




/* oberservation: the result for a given array does not change based on the order
 * we can sort nums
 * the ith element is the max 2^i times
 * so what is the min for those 2^i times?
 *   one time the ith element
 *   one time the i-1th element
 *   two times the i-2th element
 *   four times the i-3th element
 *   ... and so one
 * so we have at each element, let a be the ith element square
 * (ab)+(ac)... simplify a(b+c+...)
 */
class Solution {
private:
    long mod = 1000000007;

    // exponention using bit manipulation
    long modular_pow(long base, long exponent) {

        long ret = 1;

        while(exponent > 0) {

            int last_bit = (exponent & 1);
            if( last_bit )
                ret = (ret * base) % mod;

            base = (base * base) % mod;

            exponent = exponent >> 1;
        }

        return ret;
    }

public:
    int sumOfPower(vector<int>& nums) {
        int n = nums.size();
        sort(nums.begin(),nums.end());

        // nums = {a}
        // a^2 * (a)
        long sum = modular_pow(nums[0],3);

        if( n == 1 )
            return sum;

        // nums = {a,b}
        // (a^2 * (a)) + (b^2 * (b + 1*a)
        //  ---------                ---
        //     sum                    t
        long t = nums[0];
        sum = (sum + (modular_pow(nums[1],2) * (nums[1] + t))) % mod;
        if( n == 2 )
            return sum;

        for(int i = 2; i < n; ++i) {
            t = (nums[i-1] + ((2 * t) % mod)) % mod;
            sum = (sum + ((modular_pow(nums[i],2) * ((nums[i] + t) % mod)) % mod)) % mod;
        }

        return sum;
    }
};
