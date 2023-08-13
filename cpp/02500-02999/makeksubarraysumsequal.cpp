
// 2607. Make K-Subarray Sums Equal
// https://leetcode.com/problems/make-k-subarray-sums-equal/



/* if we slide a window of length k across arr, and the
 * sum of said window is supposed to be the same for all windows,
 * then the element that comes out of the window must be replaced
 * with the element that comes into the window of the same value
 * more formerly: arr[i] == arr[(i+k)%n] for 0 <= i < n
 *              xxx
 *    0123456789012  arr.size() = 10, k = 3
 *    ---
 *     ---
 *      ---
 *    ...
 *             ---
 * then the problem becomes to make the elements of these
 * individual arrays the same
 */
class Solution {
private:
    // recursive function to return gcd of a and b
    long long gcd(long long int a, long long int b) {
        if( b == 0 )
            return a;
        return gcd(b,a % b);
    }

    // https://leetcode.com/problems/minimum-moves-to-equal-array-elements-ii/
    long long minMoves(vector<int>& nums) {
        int n = nums.size();
        if( n == 1 )
            return 0;

        sort(nums.begin(),nums.end());
        long long med = nums[n/2]; // median
        long long ret = 0;
        for(int i = 0; i < n; ++i)
            ret += abs(med-nums[i]);

        return ret;
    }


public:
    long long makeSubKSumEqual(vector<int>& arr, int k) {
        int n = arr.size();
        if( n == 1 )
            return 0;

        long long ans = 0;

        long long _gcd = gcd(n,k);

        for(int i = 0; i < _gcd; ++i) {
            vector<int> a;
            for(int j = i; j < n; j += _gcd)
                a.push_back(arr[j]);
            ans += minMoves(a);
        }

        return ans;
    }
};
