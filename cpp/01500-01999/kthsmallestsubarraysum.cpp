
// 1918. Kth Smallest Subarray Sum
// https://leetcode.com/problems/kth-smallest-subarray-sum/




class Solution {
private:
    int na[20001]; // number of subarrays for a given length

    // debug
    multiset<int> subarraysums(vector<int>& nums, int n) {
        // brute force
        multiset<int> ms;
        int sum;
        for(int i = 0; i < n; ++i) {
            sum = 0;
            for(int j = i; j < n; ++j) {
                sum += nums[j];
                ms.insert(sum);
            }
        }
        return ms;
    }

    int solve(vector<int>& nums, int n, int x) {
        // returns the number of subarrays with sum < x
        int cnt = 0;
        int i = 0;       // left index
        int j = 0;       // right index
        int j_pre = 0;
        int sum = 0;
        int l;          // length of sliding window
        int l_pre;      // length of overlapping window
        for(; j < n; ++j) {
            sum += nums[j];
            if( sum >= x ) {
                l = j - i + 1;
                cnt += na[l-1];
                // don't double count
                // if we have an overlap with the prior window,
                // we subtract the number of subarrays in the overlapping window
                l_pre = j_pre - i + 1;
                if( l_pre > 0 )
                    cnt -= na[l_pre-1];

                while( sum >= x && i <= j) {
                    sum -= nums[i];
                    ++i;
                }
                j_pre = j;
            }
        }
        if( sum < x ) {
            l = j - i + 1;
            cnt += na[l-1];
            // don't double count
            l_pre = j_pre - i + 1;
            if( l_pre > 0 )
                cnt -= na[l_pre-1];
        }
        return cnt;
    }

    vector<int> solve2(vector<int>& nums, int n, int x) {
        // returns the number of subarrays with sum < x
        // keeps track of the smallest sum >= x encountered
        // keeps track of the largest sum < x encountered
        int largest_sum_less_x = INT_MIN;
        int smallest_sum_greater_or_equal_x = INT_MAX;
        int cnt = 0;
        int i = 0;      // left index
        int j = 0;      // right index
        int j_pre = 0;
        int sum = 0;
        int l;          // length of sliding window
        int l_pre;      // length of overlapping window
        for(; j < n; ++j) {
            sum += nums[j];
            if( sum >= x ) {
                l = j - i + 1;
                cnt += na[l-1];
                // don't double count
                // if we have an overlap with the prior window,
                // we subtract the number of subarrays in the overlapping window
                l_pre = j_pre - i + 1;
                if( l_pre > 0 )
                    cnt -= na[l_pre-1];

                while( sum >= x && i <= j) {
                    smallest_sum_greater_or_equal_x = min(smallest_sum_greater_or_equal_x,sum);
                    sum -= nums[i];
                    ++i;
                }
                j_pre = j;
            }
            if( sum < x )
                largest_sum_less_x = max(largest_sum_less_x,sum);
        }
        if( sum >= x ) {
            smallest_sum_greater_or_equal_x = min(smallest_sum_greater_or_equal_x,sum);
        } else {
            largest_sum_less_x = max(largest_sum_less_x,sum);
            l = j - i + 1;
            cnt += na[l-1];
            // don't double count
            l_pre = j_pre - i + 1;
            if( l_pre > 0 )
                cnt -= na[l_pre-1];
        }
        return {cnt,largest_sum_less_x,smallest_sum_greater_or_equal_x};
    }

    int search(vector<int>& nums, int n, int s, int e, int k) {
        if( s > e )
            return -1;

        int mid = s + ((e-s)/2);

        int cnt = solve(nums,n,mid); // number of subarrays with sum < mid
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
    int kthSmallestSubarraySum(vector<int>& nums, int k) {
        int n = nums.size(); // 1 <= n <= 20000
        // 1 <= nums[i] <= 50000
        // max possible subarray sum 1000000000 < 2147483647 (INT_MAX)

        /*
        // debug
        multiset<int> ss = subarraysums(nums,n);
        for(auto it = ss.begin(); it != ss.end(); ++it)
            cout << *it << " ";
        cout << endl;
        */

        // smallest non-empty subarray sum is min element in num
        // greatest non-empty subarray sum is sum of all elements in num
        int s = INT_MAX;
        int e = 0;
        for(int i = 0; i < n; ++i) {
            e += nums[i];
            s = min(s,nums[i]);
        }

        na[0] = 0;
        for(int i = 1; i <= 20000; ++i)
            na[i] = na[i-1] + i;

        // find the sum  x, for which there are k or less subarrays with a subarraysum < sum
        int x = search(nums,n,s,e,k);
        // cout << "x " << x << endl;
        // x is the subarray sum, for which there are k or less subarrays, with sums less than x
        // x itself may or may not be a subarray sum that exists
        // if the number of subarrays with sum less than x is less then k,
        //    then x is our answer if x exists
        //    else the answer is the next greater then x subarray sum that exists
        // else if the number of subarrays with sum less that x is equal k,
        //    then the answer is the next smaller than x subarray sum that exists

        vector<int> v = solve2(nums,n,x);
        int cnt = v[0];
        int largest_sum_less_x = v[1];
        int smallest_sum_greater_or_equal_x = v[2];
        // cout << "cnt of subarray sums less than x " << cnt << endl;
        // cout << "largest_sum_less_x               " << largest_sum_less_x << endl;
        // cout << "smallest_sum_greater_or_equal_x  " << smallest_sum_greater_or_equal_x << endl;
        if( cnt < k )
            return smallest_sum_greater_or_equal_x;
        else
            return largest_sum_less_x;
    }
};
