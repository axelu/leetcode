
// 1250. Check If It Is a Good Array
// https://leetcode.com/problems/check-if-it-is-a-good-array/




/* from hint #1 and #2: Bézout's idendtity aka Bézout's lemma
 *     https://en.wikipedia.org/wiki/B%C3%A9zout%27s_identity
 *         Let a and b be integers with greatest common divisor d.
 *         Then there exist integers x and y such that ax + by = d.
 *     So for this problem then: d = gcd(a,b) = 1 ->   ax + by = 1
 *     A generalization of Bézout's idendtity is:
 *         for more than two integers: if gcd (a1, a2, …, an) = d
 *         then there are integers x1, x2, …, xn
 *         such that d = a1 * x1 + a2 * x2 + ⋯ + an * xn
 *     So for our problem, if we calculate the successive gcd and
 *     it becomes 1, then we have a "good" array
 */
class Solution {
private:
    // recursive function to return gcd of a and b
    long long gcd(long long int a, long long int b) {
        if( b == 0 )
            return a;
        return gcd(b,a % b);
    }

public:
    bool isGoodArray(vector<int>& nums) {
        if( nums.size() == 1 )
            return nums[0] == 1;

        long long _gcd = nums[0];
        for(int x: nums) {
            _gcd = gcd(_gcd,x);
            if( _gcd == 1LL )
                return true;
        }

        return false;
    }
};
