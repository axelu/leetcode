
// 689. Maximum Sum of 3 Non-Overlapping Subarrays
// https://leetcode.com/problems/maximum-sum-of-3-non-overlapping-subarrays/



class Solution {
public:
    vector<int> maxSumOfThreeSubarrays(vector<int>& nums, int k) {
        int n = nums.size();

        // lets create all sums for subarrays of length k
        int ksum[n]; // ksum[i] = sum of k elements starting at index i with 0 <= i <= n-k
        int t = 0;
        for(int i = 0; i < n; ++i) {
            t += nums[i];
            if( i >= k-1 ) {
                ksum[i-k+1] = t;
                t -= nums[i-k+1];
            }
        }

        // debug
        // for( int i = 0; i <= n-k; ++i)
        //     cout << "ksum[" << i << "] " << ksum[i] << endl;

       // round 1: rightmost subarray
        // going from right to left
        // starting left index of rightmost subarray: n - k
        // ending left index of rightmost subarray:   2 * k
        int rsum[n]; // max sum of a subarray of length k starting at index [i,n-k]
        rsum[n-k] = ksum[n-k];
        int ridx[n]; // index at which subarray with max sum encountered so far starts
        ridx[n-k] = n-k;
        for(int i = n-k-1; i >= 2*k; --i) {
            if( ksum[i] >= rsum[i+1] ) {
                rsum[i] = ksum[i];
                ridx[i] = i;
            } else {
                rsum[i] = rsum[i+1];
                ridx[i] = ridx[i+1];
            }
        }

        // debug
        // for(int i = n-k; i >= 2*k; --i)
        //     cout << "i " << i << " rsum " << rsum[i] << " ridx " << ridx[i] << endl;


        // round 2 - middle subarray
        // going from right to left
        // starting left index of middle subarray: n - 2 * k
        // ending left index of middle subarray:   k
        int msum[n]; // max sum of a subarray of length k starting at index [i,n-2*k] AND
                     // a second array starting at j with i+k <= j <= n-k
        msum[n-2*k] = ksum[n-2*k] + rsum[n-k]; // = ksum[n-2*k] + ksum[n-k]
        array<int,2> midx[n]; // indicies of middle and right array making up msum
        midx[n-2*k] = {n-2*k,n-k};
        for(int i = n-2*k-1; i >= k; --i) {
            if( ksum[i] + rsum[i+k] >= msum[i+1] ) {
                msum[i] = ksum[i] + rsum[i+k];
                midx[i] = {i,ridx[i+k]};
            } else {
                msum[i] = msum[i+1];
                midx[i] = midx[i+1];
            }
        }

        // debug
        // for(int i = n-2*k; i >= k; --i)
        //     cout << "i " << i << " msum " << msum[i] << " midx " << midx[i][0] << " " << midx[i][1] << endl;


        // round 3 - left subarray (final round)
        // going from right to left
        // starting left index of left subarray: n - 3 * k
        // ending left index of left subarray:   0
        int lsum[n]; // max sum of a subarray of length k starting at index [i,n-3*k] AND
                  // max of the corresponding two max sum subarrays to the right
        lsum[n-3*k] = ksum[n-3*k] + msum[n-2*k];
        array<int,3> lidx[n]; // indicies of middle and right array making up msum
        lidx[n-3*k] = {n-3*k,n-2*k,n-k};
        for(int i = n-3*k-1; i >= 0; --i) {
            if( ksum[i] + msum[i+k] >= lsum[i+1] ) {
                lsum[i] = ksum[i] + msum[i+k];
                lidx[i] = {i,midx[i+k][0],midx[i+k][1]};
            } else {
                lsum[i] = lsum[i+1];
                lidx[i] = lidx[i+1];
            }
        }

        // debug
        // for(int i = n-3*k; i >= 0; --i)
        //    cout << "i " << i << " lsum " << lsum[i] << " lidx " << lidx[i][0] << " " << lidx[i][1] << " " << lidx[i][2] << endl;


        return {lidx[0][0],lidx[0][1],lidx[0][2]};
    }
};
