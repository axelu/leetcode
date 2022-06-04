
// 719. Find K-th Smallest Pair Distance
// https://leetcode.com/problems/find-k-th-smallest-pair-distance/




// see also // https://leetcode.com/problems/kth-smallest-subarray-sum/

class Solution {
private:
    int solve(vector<int>& nums, int n, int x) {
        // returns number of pairs with an absolute difference < x
        int cnt = 0;
        int i = 0;       // left index
        int j = 1;       // right index
        int j_pre = 0;
        int l;          // length of sliding window
        int l_pre;      // length of overlapping window
        for(; j < n; ++j) {
            if( nums[j] - nums[i] >= x ) {
                l = j - i;
                cnt += l * (l-1)/2;
                // don't double count
                // if we have an overlap with the prior window,
                // we subtract the number of pairs in the overlapping window
                l_pre = j_pre - i;
                if( l_pre > 0 )
                    cnt -= l_pre * (l_pre-1)/2;

                while( nums[j] - nums[i] >= x && i <= j) {
                    ++i;
                }
                j_pre = j;
            }
        }
        if( nums[j-1] - nums[i] < x ) {
            l = j - i;
            cnt += l * (l-1)/2;
            // don't double count
            l_pre = j_pre - i;
            if( l_pre > 0 )
                cnt -= l_pre * (l_pre-1)/2;
        }

        return cnt;
    }

    vector<int> solve2(vector<int>& nums, int n, int x) {
        // returns number of pairs with an absolute difference < x
        // keeps track of the smallest diff >= x encountered
        // keeps track of the largest diff < x encountered
        int largest_diff_less_x = INT_MIN;
        int smallest_diff_greater_or_equal_x = INT_MAX;
        int cnt = 0;
        int i = 0;      // left index
        int j = 1;      // right index
        int j_pre = 0;
        int l;          // length of sliding window
        int l_pre;      // length of overlapping window
        for(; j < n; ++j) {
            if( nums[j] - nums[i] >= x ) {
                l = j - i;
                cnt += l * (l-1)/2;
                // don't double count
                // if we have an overlap with the prior window,
                // we subtract the number of subarrays in the overlapping window
                l_pre = j_pre - i;
                if( l_pre > 0 )
                    cnt -= l_pre * (l_pre-1)/2;

                while( nums[j] - nums[i] >= x && i <= j) {
                    smallest_diff_greater_or_equal_x = min(smallest_diff_greater_or_equal_x,nums[j] - nums[i]);
                    ++i;
                }
                j_pre = j;
            }
            if( nums[j] - nums[i] < x )
                largest_diff_less_x = max(largest_diff_less_x,nums[j] - nums[i]);
        }
        if( nums[j] - nums[i] >= x ) {
            smallest_diff_greater_or_equal_x = min(smallest_diff_greater_or_equal_x,nums[j] - nums[i]);
        } else {
            largest_diff_less_x = max(largest_diff_less_x,nums[j] - nums[i]);
            l = j - i;
            cnt += l * (l-1)/2;
            // don't double count
            l_pre = j_pre - i;
            if( l_pre > 0 )
                cnt -= l_pre * (l_pre-1)/2;
        }
        return {cnt,largest_diff_less_x,smallest_diff_greater_or_equal_x};
    }

    // binary search
    int search(vector<int>& nums, int n, int s, int e, int k) {
        if( s > e )
            return -1;

        int mid = s + ((e-s)/2);
        int cnt = solve(nums,n,mid); // number of pairs with diff < mid
        if( cnt == k ) {
            return mid;
        } else if( cnt < k ) {
            // can we do better?
            int t = search(nums,n,mid+1,e,k);
            return t != -1 ? t : mid;
        } else {
            return search(nums,n,s,mid-1,k);
        }
    }

public:
    int smallestDistancePair(vector<int>& nums, int k) {
        int n = nums.size(); // 2 <= n <= 10^4
        // 0 <= nums[i] <= 10^6
        // 1 <= k <= n * (n - 1) / 2

        // min diff between any pair could be 0 (duplicate)
        // max diff is max_element - min_element
        sort(nums.begin(),nums.end());
        int mx = nums[n-1] - nums[0];

        // find the difference x for which there are k or less pairs with
        // abs(nums[i]-nums[j]) < x where 0 <= i < j < n
        int x = search(nums,n,0,mx,k);
        // cout << "x " << x << endl;
        // x is a difference for which there are k or less pairs with a pairdiff < x
        // x may or may not be a difference that exists in nums
        // if the number of pairs with diff less than x is less than k,
        //    then x is our answer if x exists
        //    else the answer is the next greater then x difference that exists
        // else if the number of pairs with difference less than x is equal k,
        //    then the answer is the next smaller than x difference that exists

        vector<int> v = solve2(nums,n,x);
        int cnt = v[0];
        int largest_diff_less_x = v[1];
        int smallest_diff_greater_or_equal_x = v[2];
        // cout << "cnt of pairs with diff less than x " << cnt << endl;
        // cout << "largest_diff_less_x                " << largest_diff_less_x << endl;
        // cout << "smallest_diff_greater_or_equal_x   " << smallest_diff_greater_or_equal_x << endl;
        if( cnt < k )
            return smallest_diff_greater_or_equal_x;
        else
            return largest_diff_less_x;
    }
};
