
// 3209. Number of Subarrays With AND Value of K
// https://leetcode.com/problems/number-of-subarrays-with-and-value-of-k/






class Solution {
private:
    // we will index bits from right to left
    // 987654321098765432109876543210




public:
    long long countSubarrays(vector<int>& nums, int k) {
        // for a bit in k that is set
        //     ALL members of a given subarray need to have that bit set
        // for a bit in k that is not set
        //     at least one member of a given subarray must have that bit not set
        // so we could use each position as a pivot point
        //     and look into both directions to see when the condition is first met and how far beyond that it is met
        //     that becomes our pivot
        //             x
        //               f  l
        //     01234567890123456789
        // we need to not doublecount however!

        int n = nums.size();

        bool kbits[30]; // 30 because 0 <= nums[i], k <= 1e9, 1e9 binary 111011100110101100101000000000 has 30 digits
        memset(kbits,false,sizeof kbits);
        for(int i = 0; i < 30; ++i) {
            if( k & (1<<i) ) {
                kbits[i] = true;
            }
        }
        /*
        for(int i = 29; i >= 0; --i)
            cout << kbits[i];
        cout << endl;
        */

        int lft[n][30]; // next position to the left and including the current position where bit is not set
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < 30; ++j) {
                if( nums[i] & (1<<j) ) {
                    if( i > 0 )
                        lft[i][j] = lft[i-1][j];
                    else
                        lft[i][j] = -1;
                } else {
                    lft[i][j] = i;
                }
            }
        }

        int rgt[n][30]; // next position to the right and including the current position where bit is not set
        for(int i = n-1; i >= 0; --i) {
            for(int j = 0; j < 30; ++j) {
                if( nums[i] & (1<<j) ) {
                    if( i < n-1 )
                        rgt[i][j] = rgt[i+1][j];
                    else
                        rgt[i][j] = n;
                } else {
                    rgt[i][j] = i;
                }
            }
        }

        long long ans = 0;

        for(int i = 0; i < n; ++i) {
            // cout << "i " << i << endl;

            // if any of the set bits in k are not set in nums[i],
            // nums[i] can never be a part of a subarray with AND value of k
            // in this case we advance
            if( (nums[i] & k) != k )
                continue;

            // look to the left
            // for each bit in k and in nums[i]
            //    k bit   nums[i] bit
            //   ---------------------
            // A not set    not set   irrelevant
            // B   set      not set   already eliminated
            // C not set      set     look for first position to the left where nums[pos] k bit not set
            //                        in other words: we need to at least span C,i to get to a 0 for this bit
            //                        hence we are looking for the minimum C
            // D   set        set     look for the first position where nums[pos] k bit not set
            // for C and D there are possible outcomes
            //          x
            // 01234567890123456789
            //      C
            //      D
            // at C we would have the bit not set, but because C == D, we would have another bit set that we need set
            // so we have no solution
            // 01234567890123456789
            //      C
            //       D
            // same problem -> no solution
            // 01234567890123456789
            //      C
            //     D
            // we have a solution between D+1,x and C,x
            // we can generalize:
            // look for min C (min based on position) and max D (max based on position)
            // if max D < min C we have a solution: how many? min C - (max D + 1) + 1
            // now we look to the right and see how long we meet the criteria
            // for case C not relevant
            // for case D we look for the 1st not set bit to the right
            // again for every bit we look to to find min R when for case C and D, so basically bit not set
            // example
            //          x
            // 01234567890123456789
            //        C
            //    D----  --R
            // that gives us R - x, so combining we get (min C - (max D + 1) + 1) * (R-x) subarrays

            // we can do the same to the right
            // and after have to subtract the double count

            int C = i;
            int D = -1;
            int R = n;
            for(int j = 0; j < 30; ++j) {
                if( !(nums[i] & (1<<j)) )
                    continue;

                if( !kbits[j] ) {
                    C = min(C, lft[i][j]);
                } else {
                    D = max(D, lft[i][j]);
                    R = min(R, rgt[i][j]);
                }
            }
            // cout << "C " << C << " D " << D << " R " << R << endl;
            if( D >= C )
                continue;

            // long long t = (long long)(C - D) * (long long)(R - i);
            long long t = (long long)(C - D);
            // cout << "subarrays t " << t << endl;
            ans += t;








        }

        return ans;
    }
};
