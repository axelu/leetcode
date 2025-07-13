
// 3533. Concatenated Divisibility
// https://leetcode.com/problems/concatenated-divisibility/




/* To find the overall remainder in a Remainders and Addition problem,
 * find the remainder of each term separately and then add them together.
 *
 */

class Solution {
private:
    int countSetBits(int i) {
        unsigned int count = 0;
        while (i) {
            count += i & 1;
            i >>= 1;
        }
        return count;
    }

    int get_magnitude(int x) {
        // 1 <- x <- 1e5
        if( x < 10 )
            return 10;
        else if( x < 100 )
            return 100;
        else if( x < 1000 )
            return 1000;
        else if( x < 10000 )
            return 10000;
        else if( x < 100000 )
            return 100000;
        else
            return 1000000;
    }

    vector<int> t;

    // mask worst case:
    //     we could have 13 elements in nums -> binary 1111111111111 -> decimal 8191
    // remainder worst case: 1 <= k<= 100 -> 99, so 0-99
    // hence states 8191 * 100 = 819100

    int mem[8192][100];

    int rec(vector<int>& nums, int mask, int rem, int k) {
        int n = nums.size();

        if( mask == pow(2,n)-1 ) {
            // we used all elements of nums
            // if our remainder is 0, then we have a Solution
            /*
            cout << rem << " ";
            for(int i = 0; i < t.size(); ++i)
                cout << t[i] << ":";
            cout << endl;
            */
            return rem;
        }

        if( mem[mask][rem] != 1 )
            return mem[mask][rem];

        // which position in our answer are we filling in?
        int pos = countSetBits(mask);

        int ret = -1;

        // we have a choice
        //    use any of the unused integers in nums
        for(int i = 0; i < n; ++i) {
            if( mask & (1<<i) )
                continue;

            // TODO we should keep track of nums[i] already tried
            //      as we don't need to try same value over and over

            // first we would need to multiply the number we have so far
            // because we are doing concatination, then we can add nums[i]
            // exmples:
            // let our number so far be 675
            // if nums[i] = 7  -> mulitply the number we have so far with 10, then add 7
            //                          675 * 10 = 6750
            //                                     6750 + 7 = 6757
            // if nums[i] = 84 -> multiply the number we have so far with 100
            //                          675 * 100 = 67500
            //                                      67500 + 84 = 67584
            // we need to track the remainder accross those operations !!!
            int magnitude = get_magnitude(nums[i]);
            int magnitude_rem = magnitude % k;
            // remainder after we would multiply number so far with magnitude
            int op1_rem = (rem * magnitude_rem) % k;
            // remainder after we would add nums[i] to our new number
            int new_rem = (op1_rem + (nums[i] % k)) % k;

            int lret = rec(nums, mask | (1<<i), new_rem, k);
            if( lret == 0 ) {
                t[pos] = nums[i];
                return mem[mask][rem] = 0;
            }
        }

        return mem[mask][rem] = ret;
    }

public:
    vector<int> concatenatedDivisibility(vector<int>& nums, int k) {
        int n = nums.size();

        for(int i = 0; i < pow(2,n); ++i)
            for(int j = 0; j < k; ++j)
                mem[i][j] = 1;

        sort(nums.begin(),nums.end());
        t.resize(n);

        if( rec(nums, 0, 0, k) == -1 )
            return {};
        else
            return t;
    }
};
