
// 3776. Minimum Moves to Balance Circular Array
// https://leetcode.com/problems/minimum-moves-to-balance-circular-array/



/* example
 * let sum_posval be the sum of all balance[i] > 0
 * let val_negval balance[i] < 0
 * case sum_posval == val_negval
 *   0   1  2  3  4
 * [ 1,-16, 2, 3,10] -> ans = 29
 * let us extend balance as it is circular around the neg position i=1
 * we get:
 *            0   1  2  3  4    balance index
 *   0  1  2  3      4  5  6  7 nums and new array index
 *   2  3 10  1 -16  2  3 10  1 nums
 *   4  3  2  1      1  2  3  4 factor = distance from neg position
 *   8  9 20  1      2  6 30  4 new array
 * let us remove the negative positon from nums and new array
 *   0  1  2  3  4  5   6  7    nums and new array index
 *   2  3 10  1  2  3  10  1    nums
 *   8  9 20  1  2  6  30  4    new arr
 * now sliding window of length n-1, smallest sum is our answer
 *   8  9 20  1  2  6  30  4
 * ------------              sliding window sum 38
 *    ------------           sliding window sum 32
 *       ------------        sliding window sum 29 <- best = our anwer
 *          ------------     sliding window sum 39
 *             ------------  sliding window sum 42
 */
class Solution {
private:
    void fill_nums(vector<int>& balance, int n, int idx_negval, vector<int>& arr, int len) {
        if( idx_negval < n-1 ) {
            int i = 0; // index in arr
            for(int j = idx_negval+1; j < n; ++j) {
                arr[i] = balance[j];
                ++i;
            }
            for(int j = 0; j < n; ++j) {
                if( j == idx_negval ) {
                    continue;
                }
                arr[i] = balance[j];
                ++i;
            }
            for(int j = 0; j < idx_negval; ++j) {
                arr[i] = balance[j];
                ++i;
            }

        } else { // idx_negval == n-1
            int i = 0; // index in arr
            for(int j = 0; j < n-1; ++j) {
                arr[i] = balance[j];
                ++i;
            }
            for(int j = 0; j < n-1; ++j) {
                arr[i] = balance[j];
                ++i;
            }
        }

        return;
    }

    void fill_arr(vector<int>& balance, int n, int idx_negval, vector<long long>& arr, int len) {
        if( idx_negval < n-1 ) {
            int i = 0; // index in arr
            long long f = n-1;
            long long addend = -1;
            for(int j = idx_negval+1; j < n; ++j) {
                arr[i] = (long long)balance[j] * f;
                f += addend;
                ++i;
            }
            for(int j = 0; j < n; ++j) {
                if( j == idx_negval ) {
                    f = 1;
                    addend = 1;
                    continue;
                }
                arr[i] = (long long)balance[j] * f;
                f += addend;
                ++i;
            }
            for(int j = 0; j < idx_negval; ++j) {
                arr[i] = (long long)balance[j] * f;
                f += addend;
                ++i;
            }

        } else { // idx_negval == n-1
            int i = 0; // index in arr
            long long f = n-1;
            for(int j = 0; j < n-1; ++j) {
                arr[i] = (long long)balance[j] * f;
                --f;
                ++i;
            }
            f = 1;
            for(int j = 0; j < n-1; ++j) {
                arr[i] = (long long)balance[j] * f;
                ++f;
                ++i;
            }
        }

        return;
    }

    long long solve(vector<long long>& arr, int len, int n) {
        // guaranteed sum of positive values == val_negval

        long long ret = LLONG_MAX;

        // sliding window of length n-1
        long long sum = 0LL;
        int i = 0;                     // left index
        for(int j = 0; j < len; ++j) { // right index
            sum += (long long)arr[j];
            if( j-i+1 == n-1 ) {
                ret = min(ret, sum);
                sum -= (long long)arr[i];
                ++i;
            }
        }

        return ret;
    }

    long long solve(
        vector<long long>& lftPrefixSum,
        vector<long long>& lftPrefixSumMoves,
        vector<long long>& rgtPrefixSum,
        vector<long long>& rgtPrefixSumMoves,
        int n,
        int len,
        int val_negval)
    {
        long long ans = LLONG_MAX;

        // sliding window
        int j = 1;                          // index in rgtPrefixSum
        for(int i = len/2; i >= 0; --i) {   // index in lftPrefixSum
            if( lftPrefixSum[i] == val_negval * -1LL ) {
                // we can move all to the right and be done
                ans = min(ans, lftPrefixSumMoves[i]);

            } else if( lftPrefixSum[i] > val_negval * -1LL ) {
                if( lftPrefixSum[i-1] >= val_negval * -1LL )
                    continue;

                // lftPrefixSum[i-1] < val_negval * -1LL
                // we don't need help from the right half yet
                // we need to move all i-1 and 'some' of us
                // how many do we move of us?
                long long t = (val_negval * -1LL) - lftPrefixSum[i-1];
                long long t_moves = t * (long long)i;
                ans = min(ans, t_moves + lftPrefixSumMoves[i-1]);

            } else { // lftPrefixSum[i] < val_negval * -1LL
                // we need help from the right half

                // how many do we need to move from the right half?
                // our window max length is n-1 !!!
                // the slice in our left half is i long
                // the slice in our right half is j long
                // extend our window, but not beyond our max length
                while( (lftPrefixSum[i] + rgtPrefixSum[j]) < (val_negval * -1LL) && i + j + 1 <= n-1 )
                    ++j;
                if( (lftPrefixSum[i] + rgtPrefixSum[j]) < (val_negval * -1LL) )
                    continue;
                // if( i > 0 && (lftPrefixSum[i-1] + rgtPrefixSum[j]) > (val_negval * -1LL) )
                //     continue;

                if( (lftPrefixSum[i] + rgtPrefixSum[j]) == (val_negval * -1LL) ) {
                    // we must take all from left and right
                    ans = min(ans, lftPrefixSumMoves[i] + rgtPrefixSumMoves[j]);

                } else { // (lftPrefixSum[i] + rgtPrefixSum[j]) > (val_negval * -1LL)
                    // we have a surplus
                    // long long surplus = (lftPrefixSum[i] + rgtPrefixSum[j]) - (val_negval * -1LL);
                    // we greedily pull all from the shorter side
                    if( i < j ) {
                        // we take all from left aka i
                        // we take all from right j-1
                        // we take only from j what we need, which is t
                        long long t = (val_negval * -1LL) - lftPrefixSum[i] - rgtPrefixSum[j-1];
                        if( t < 0 )
                            continue;
                        long long t_moves = t * (long long)j;
                        ans = min(ans, lftPrefixSumMoves[i] + rgtPrefixSumMoves[j-1] + t_moves);

                    } else {
                        // ?? i == 0 < j, but then problem with lftPrefixSum[i-1]
                        long long t = (val_negval * -1LL) - lftPrefixSum[i-1] - rgtPrefixSum[j];
                        if( t < 0 )
                            continue;
                        long long t_moves = t * (long long)i;
                        ans = min(ans, t_moves + lftPrefixSumMoves[i-1] + rgtPrefixSumMoves[j]);
                    }
                }
            }
            // cout << "i " << i << " ans " << ans << endl;
        }
        return ans;
    }

public:
    long long minMoves(vector<int>& balance) {
        int n = balance.size(); // 1 <= n <= 1e5

        // -1 * 1e9 <= balance[i] <= 1e9
        // There is at most one negative value in balance initially.

        int idx_negval = -1; // index of negative value in balance
        int val_negval;      // value of negative value in balance
        long long sum_posval = 0LL;
        for(int i = 0; i < n; ++i) {
            int val = balance[i];
            if( val < 0 ) {
                idx_negval = i;
                val_negval = val;
            } else {
                sum_posval += (long long)val;
            }
        }

        // edge case there is no negative value in balance
        if( idx_negval == -1 )
            return 0LL;

        // edge case the sum of positive values < (val_negval * -1LL)
        if( sum_posval < val_negval * -1LL )
            return -1LL;

        // edge case n == 2
        if( n == 2 )
            return (val_negval * -1LL);

        // edge case sum of immediate adjacent values >= (val_negval * -1LL)
        long long val_lft = idx_negval == 0 ? balance[n-1] : balance[idx_negval-1];
        long long val_rgt = idx_negval == n-1 ? balance[0] : balance[idx_negval+1];
        if( val_lft + val_rgt >= (val_negval * -1LL) )
            return (val_negval * -1LL);

        // construct "new arr" (see above explanation)
        int len = (n-1) * 2; // length of our new array
        vector<long long> arr(len);
        fill_arr(balance, n, idx_negval, arr, len);

        // edge case the sum of positive values == (val_negval * -1LL)
        if( sum_posval == val_negval * -1LL )
            return solve(arr, len, n);

        // we know len is even
        // we know in the middle between the left and right half
        // would be our negative value
        // 0  1  2  3  4  5  6  7  8  9 10 11 index new array
        // ---left half----|---right half----
        // 5  4  3  2  1  0  0  1  2  3  4  5 index prefixSums left right
        // example [3,5,-10,3,3,2,5]

        // construct "nums" (see above explanation)
        vector<int> nums(len);
        fill_nums(balance, n, idx_negval, nums, len);

        vector<long long> lftPrefixSum((len/2)+1, 0LL);
        vector<long long> lftPrefixSumMoves((len/2)+1, 0LL);
        for(int j = 1, i = (len/2)-1; j <= (len/2); ++j,--i) {
            lftPrefixSum[j] = lftPrefixSum[j-1] + (long long)nums[i];
            lftPrefixSumMoves[j] = lftPrefixSumMoves[j-1] + arr[i];
        }
        vector<long long>rgtPrefixSum((len/2)+1, 0LL);
        vector<long long>rgtPrefixSumMoves((len/2)+1, 0LL);
        for(int j = 1, i = len/2; j <= (len/2); ++j,++i) {
            rgtPrefixSum[j] = rgtPrefixSum[j-1] + (long long)nums[i];
            rgtPrefixSumMoves[j] = rgtPrefixSumMoves[j-1] + arr[i];
        }

        long long ans = solve(lftPrefixSum, lftPrefixSumMoves, rgtPrefixSum, rgtPrefixSumMoves, n, len, val_negval);
        ans = min(ans, solve(rgtPrefixSum, rgtPrefixSumMoves, lftPrefixSum, lftPrefixSumMoves, n, len, val_negval));

        return ans;
    }
};
