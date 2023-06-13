
// 2557. Maximum Number of Integers to Choose From a Range II
// https://leetcode.com/problems/maximum-number-of-integers-to-choose-from-a-range-ii/



/* extreme test case
 * banned = {1}, n = 10^9
 * maxSum = 10^15
 *


 */
class Solution {
public:
    int maxCount(vector<int>& banned, int n, long long maxSum) {

        sort(banned.begin(),banned.end());
        int banned_sz = banned.size();
        int i = 0; // index in banned

        long long sum = 0;
        long long k = 1;
        int ans = 0;
        while( k <= n ) {
            if( sum + k > maxSum )
                break;

            if( i < banned_sz && banned[i] == k ) {
                ++i;
                while( i < banned_sz && banned[i-1] == banned[i] ) {
                    ++i;
                }
                ++k;
                continue;
            }
            sum += k;
            ++ans;
            ++k;

        }

        return ans;
    }
};
