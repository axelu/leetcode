
// 2111. Minimum Operations to Make the Array K-Increasing
// https://leetcode.com/problems/minimum-operations-to-make-the-array-k-increasing/

// resource
// https://www.geeksforgeeks.org/longest-monotonically-increasing-subsequence-size-n-log-n/


class Solution {
private:
    // binary search
    int upper_bound(int nums[], int n, int target) {
        // returns 'n' if nums[n-1] <= target
        // returns  0  if nums[0] > target
        // binary search upper bound while loop
        // upper bound -> greater than target
        int s = 0;
        int e = n; // n = nums.size()
        int mid;
        while(s < e) {
            mid = s + ((e-s)/2);
            if( target >= nums[mid] )
                s = mid + 1;
            else
                e = mid;
        }
        if( s < n && nums[s] <= target )
            ++s;

        return s;
    }
    
    int solve(vector<int>& arr, int n, int s, int k) {
        // cout << "solve s " << s << endl;
        
        // longest non-decreasing subsequence
        int lnds[n/k+1];
        lnds[0] = arr[s];
        
        int llnds = 1; // length of longest non-decreasing subsequence
        
        int i_idx = 0;
        for(int i = s + k; i < n; i += k) {
            // cout << "i " << i << endl;
            
            ++i_idx;
            // cout << "i_idx " << i_idx << endl;
            
            if( arr[i] < lnds[0]) {
                // new smallest value
                lnds[0] = arr[i];

            } else if( arr[i] >= lnds[llnds - 1] ) {
                // arr[i] extends largest subsequence
                lnds[llnds++] = arr[i];

            } else {
                lnds[upper_bound(lnds,llnds,arr[i])] = arr[i];
            }
        }
        
        return (i_idx + 1) - llnds;
    }
    
public:
    int kIncreasing(vector<int>& arr, int k) {
        int n = arr.size();
        // cout << "n " << n << endl;
        
        int ans = 0;
        for(int i = 0; i < k; ++i)
            ans += solve(arr,n,i,k);
        
        return ans;
    }
};
