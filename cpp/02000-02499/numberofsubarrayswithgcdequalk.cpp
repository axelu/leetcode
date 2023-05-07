
// 2447. Number of Subarrays With GCD Equal to K
// https://leetcode.com/problems/number-of-subarrays-with-gcd-equal-to-k/




class Solution {
private:
    // recursive function to return gcd of a and b
    long long gcd(long long int a, long long int b) {
        if( b == 0 )
            return a;
        return gcd(b,a % b);
    }

public:
    int subarrayGCD(vector<int>& nums, int k) {
        int n = nums.size();
        if( n == 1 )
            return nums[0] == k ? 1 : 0;

        // the GCD at a given element of nums can reach k by two means:
        //    either the element of nums equals k OR
        //    the GCD of two adjacent elements is k
        // any subarray that traverses that where to the left and right
        //    the GCD is a multiple of k as valid subarrays
        //
        // example
        //                            0  1  2  4
        //                           18  9 12 24
        // gcd(nums[i-1],nums[i])    18  9  3 12  Note: at index 0, is gcd = nums[0]
        //                                        Note: special consideration if nums[i] == k
        // answer = 4: [19,12],[9,12,24],[18,9,12],[18,9,12,24]

        // left to right
        // holds the index to the left where a subarray begins that has gcd
        // of all adjacent cells be a multiple of k
        int l2r[n];memset(l2r,-1,sizeof l2r);
        for(int i = 1; i < n; ++i) {
            int t = gcd(nums[i-1],nums[i]);
            if( t >= k && t % k == 0 )
                l2r[i] = l2r[i-1] != -1 ? l2r[i-1] : i-1;
            else
                l2r[i] = -1;
        }
        /*
        cout << "l2r ";
        for(int i = 0; i < n; ++i)
            cout << l2r[i] << " ";
        cout << endl;
        */

        // right to left
        int r2l[n];memset(r2l,-1,sizeof r2l);
        for(int i = n-2; i >= 0; --i) {
            int t = gcd(nums[i+1],nums[i]);
            if( t >= k && t % k == 0 )
                r2l[i] = r2l[i+1] != -1 ? r2l[i+1] : i+1;
            else
                r2l[i] = -1;
        }
        /*
        cout << "r2l ";
        for(int i = 0; i < n; ++i)
            cout << r2l[i] << " ";
        cout << endl;
        */

        int ans = 0;

        int k_lastseen = -1;
        for(int i = 0; i < n; ++i) {
            if( nums[i] == k ) {
                // any subarray starting at l2r[i]...i inclusive
                // with min length i - l2r[i] + 1, max length r2l[i] - l2r[i] + 1

                // if we have seen k to the left, then we have already covered subarrays
                // ending at i

                int l;
                if( l2r[i] == -1 ) {
                    l = 1;
                } else if( l2r[i] <= k_lastseen ) {
                    if( nums[k_lastseen] != k ) {
                         l = i - (k_lastseen + 1) + 1;
                    } else {
                        l = 1;
                    }
                } else {
                    l = i - l2r[i] + 1;
                }

                int r = r2l[i] == -1 ? 1 : r2l[i] - i + 1;

                ans += l * r;
                k_lastseen = i;

            } else if( i > 0 && gcd(nums[i-1],nums[i]) == k ) {

                int l;
                if( k_lastseen == i-1 ) {
                    l = 0;
                } else if( l2r[i] <= k_lastseen ) {
                    if( nums[k_lastseen] != k ) {
                         l = (i - 1) - (k_lastseen + 1) + 1;
                    } else {
                        l = 1;
                    }
                } else {
                    l = i - l2r[i];
                }

                int r = r2l[i] == -1 ? 1 : r2l[i] - i + 1;

                ans += l * r;
                k_lastseen = i - 1;
            }
            //cout << "i " << i << " ans " << ans << endl;
        }

        return ans == 0 && k == 1 ? 1 : ans; // edge case such as [4,10,5] k = 1
    }
};
