
// 581. Shortest Unsorted Continuous Subarray
// https://leetcode.com/problems/shortest-unsorted-continuous-subarray/
// day 25 February 2021 challenge
// https://leetcode.com/explore/challenge/card/february-leetcoding-challenge-2021/587/week-4-february-22nd-february-28th/3652/





class Solution {
private:
    // binary search upper bound
    // first element greater than target
    int upperBound(vector<int>& v, int s, int e, int target) {
        if( s > e ) return -1;

        int mid = s + ((e - s)/2);
        if( v[mid] <= target ) {
            return upperBound(v,mid+1,e,target);
        } else {
            // can we do better?
            int ans = upperBound(v,s,mid-1,target);
            return ans != -1 ? ans : mid;
        }
    }

    // binary search lower bound
    // first element greater or equal than target
    int lowerBound(vector<int>& v, int s, int e, int target) {
        if( s > e ) return -1;

        int mid = s + ((e - s)/2);
        if( v[mid] >= target ) {
            // can we do better?
            int ans = lowerBound(v,s,mid-1,target);
            return ans != -1 ? ans : mid;
        } else {
            return lowerBound(v,mid+1,e,target);
        }
    }

public:
    int findUnsortedSubarray(vector<int>& nums) {
        int n = nums.size(); // 1 <= nums.length <= 10^4
        if( n == 1 ) return 0;
        if( n == 2 ) return nums[0] <= nums[1] ? 0 : 2;

        // idea:
        // find 1st occurence of an unsorted element nums[i] > nums[i+1], lets call that index s
        //    if never found the array is sorted
        // find last occurence of unsorted element nums[i] < nums[i-1], lets call that index e
        // within that range [s,e] we need to find the min and max
        // for min: we need to find where min needs to go, basically
        //          find the 1st element greater than min in the range [0,s], basically upper_bound
        //          edge case: s = 0
        //          edge case: min is smaller than even element 0
        // for max: we need to find where the max needs to go, basically
        //          find the 1st element in the range [e,n-1] that is equal or greater than max, basically lower_bound
        //          edge case: e = n-1
        //          edge case: max is greater than even element n-1

        int s = 0;
        for(; s < n-1; ++s)
            if( nums[s] > nums[s+1] ) break;
        // cout << "s " << s << endl;
        if( s == n-1 ) return 0; // array is already sorted

        int e = n-1;
        for(; e > 0; --e)
            if( nums[e] < nums[e-1] ) break;
        // cout << "e " << e << endl;

        int mn = INT_MAX, mx = INT_MIN;
        for(int i = s; i <= e; ++i) {
            if( nums[i] < mn ) mn = nums[i];
            if( nums[i] > mx ) mx = nums[i];
        }
        // cout << "mn " << mn << " mx " << mx << endl;

        int l = upperBound(nums,0,s,mn);
        // cout << "l " << l << endl;
        int r = lowerBound(nums,e,n-1,mx);
        if( r == -1 ) r = n;
        // cout << "r " << r << endl;

        return r - l;
    }
};
