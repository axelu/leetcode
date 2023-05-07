
// 2638. Count the Number of K-Free Subsets
// https://leetcode.com/problems/count-the-number-of-k-free-subsets/




/* from the hints
 *     divide nums into groups of arithmetic sequences with difference of k
 *     solve the problem for each group dp[i] = dp[i-1] + dp[i-2]
 * answer is the product of each group's answer
 *                    0  1  2  3  4
 * take a group like: 3, 6, 9,12,15
 * dp[0] = 2;                  {},{3}
 * dp[1] = 3;                  {},{3},{6}
 * dp[2] = dp[1] + dp[0] =  5; {},{3},{6},{9},{3,9}
 * dp[3] = dp[2] + dp[1] =  8; {},{3},{6},{9},{3,9},{12},{3,12},{6,12}
 * dp[4] = dp[3] + dp[2] = 13; ...
 * ...
 * ans => 13
 *
 * lets say we have 3 groups A, B and C and we solve to 2, 3 and 8 for those
 * like [3,7,10,20,23,26,29], k = 3
 * group A = {3}, group B = {7,10} and group C = {20,23,26,29}
 * now we have the following combinations
 *   A  B  C
 *   2  3  8 number of solutions (note that this counts our empty solution in each)
 *   -------
 * 1 -  -  -  1  empty solution
 * 2 -  -  x  7  Note: 8 - 1 because we cannot double count the empty solution
 * 3 -  x  -  2  Note: 3 - 1 because we cannot double count the empty solution
 * 4 -  x  x 14  2 * 7 (  (3-1) * (7-1) )
 * 5 x  -  -  1  Note: 2 - 1 because we cannot double count the empty solution
 * 6 x  -  x  7  1 * 7
 * 7 x  x  -  2  1 * 2
 * 8 x  x  x 14  1 * 2 * 7
 *          ----
 *    sum    48
 *
 * Observation: 48 = 2 * 3 * 8
 */
class Solution {
public:
    long long countTheNumOfKFreeSubsets(vector<int>& nums, int k) {
        int n = nums.size();

        // precalculate dp
        long long dp[n];
        dp[0] = 2;
        if( n > 1 )
            dp[1] = 3;
        for(int i = 2; i < n; ++i)
            dp[i] = dp[i-1] + dp[i-2];

        long long ans = 1;

        set<int> st(nums.begin(),nums.end());

        while( !st.empty() ) {
            long long l = 0; // length of arithmetic sequence - 1
            int t = *st.begin();
            st.erase(t);

            t += k;
            auto f = st.find(t);
            while( f != st.end() ) {
                ++l;
                st.erase(f);
                t += k;
                f = st.find(t);
            }

            ans *= dp[l];
        }

        return ans;
    }
};
