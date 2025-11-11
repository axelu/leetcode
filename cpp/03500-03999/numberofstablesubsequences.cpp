
// 3686. Number of Stable Subsequences
// https://leetcode.com/problems/number-of-stable-subsequences/




class Solution {
private:
    const long mod = 1000000007;


public:
    int countStableSubsequences(vector<int>& nums) {
        int n = nums.size();

        // every subsequence of length 1 is stable
        // every subsequence of length 2 is stable

        if( n == 1 )
            return 1;
        if( n == 2 )
            return 3;

        // we will go from right to left
        // what matters is how we continue
        // example
        //        0  1  2  3  4  5  6   index in nums
        //        1  0  1  1  0  0  1   parity of element in nums
        //   ------------------------------------------------------------------------
        //           3  3  2  1  1  1   count of 1s right to left up to i
        //           3  2  2  2  1  0   count of 0s right to left up to i
        //           3  3  1  0  0  0   count of stable subsequences starting with 11
        //          18 18  6  0  0  0   count of stable subsequences starting with 10
        //          26  2  2  2  1  0   count of stable subsequences starting with 01
        //           6  2  2  2  0  0   count of stable subsequences starting with 00
        //   ------------------------------------------------------------------------
        //     110  59 30 15  7  3  1

        // TODO we only need a[6] and b[6] and can flip pointers
        long a[100000][6]; memset(a, 0, sizeof a);
        if( nums[n-1] % 2 )
            a[n-1][0] = 1;
        else
            a[n-1][1] = 1;

        for(int i = n-2; i >= 0; --i) {
            if( nums[i] % 2 ) {
                // 1 count carry + 1
                a[i][0] = (a[i+1][0] + 1L) % mod;
                // 0 count unchanged carry
                a[i][1] = a[i+1][1];
                // new starting with 11
                //     carry +
                //     1 count +
                //     10 count
                a[i][2] = (((a[i+1][2] + a[i+1][0]) % mod) + a[i+1][3]) % mod;
                // new starting with 10
                //     carry +
                //     0 count +
                //     01 count +
                //     00 count
                a[i][3] = (((((a[i+1][3] + a[i+1][1]) % mod) + a[i+1][4]) % mod) + a[i+1][5]) % mod;
                // new starting with 01 unchanged carry
                a[i][4] = a[i+1][4];
                // new starting with 00 unchanged carry
                a[i][5] = a[i+1][5];

            } else {
                // 1 count unchanged carry
                a[i][0] = a[i+1][0];
                // 0 count carry + 1
                a[i][1] = (a[i+1][1] + 1) % mod;
                // new starting with 11 unchanged carry
                a[i][2] = a[i+1][2];
                // new starting with 10 unchanged carry
                a[i][3] = a[i+1][3];
                // new starting with 01
                //    carry +
                //    1 count +
                //    10 count +
                //    11 count
                a[i][4] = (((((a[i+1][4] + a[i+1][0]) % mod) + a[i+1][3]) % mod) + a[i+1][2]) % mod;
                // new starting with 00 unchanged
                //    carry +
                //    0 count +
                //    01 count
                a[i][5] = (((a[i+1][5] + a[i+1][1]) % mod) + a[i+1][4]) % mod;
            }
        }

        /*
        for(int i = 0; i < 6; ++i) {
            for(int j = 0; j < n; ++j) {
                cout << a[j][i] << " ";
            }
            cout << endl;
        }
        */

        long ans = 0;
        for(int i = 0; i < 6; ++i)
            ans = (ans + a[0][i]) % mod;


        return ans;
    }
};
