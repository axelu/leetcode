
// 3824. Minimum K to Reduce Array Within Limit
// https://leetcode.com/problems/minimum-k-to-reduce-array-within-limit/





class Solution {
private:
    int nonPositive(vector<int>& nums, int k) {
        // nums is sorted non-decreasing
        // k > 0
        int n = nums.size();
        int pre = 0;

        int ret = 0;

        int s = 0;
        int f = 1;
        while( pre < n ) {
            // returns 'n' if nums[n-1] <= target
            // returns  0  if nums[0] > target
            // binary search upper bound while loop
            // upper bound -> greater than target
            int target = f * k;
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

            ret = ret + (s-pre)*f;
            ++f;
            pre = s;
        }

        return ret;
    }

    // binary search
    int search(int s, int e, vector<int>& nums) {
        // cout << "search s " << s << " e " << e << endl;
        if( s > e )
            return -1;
        int mid = s + ((e-s)/2);
        int ops = nonPositive(nums, mid);
        long k2 = (long)mid * (long)mid;
        if( ops <= k2 ) {
            // can we do better?
            int t = search(s, mid-1, nums);
            return t != -1 ? t : mid;
        }
        return search(mid+1, e, nums);
    }

public:
    int minimumK(vector<int>& nums) {
        int n = nums.size();
        sort(begin(nums), end(nums));

        // int tt1 = nonPositive(nums, 3); cout << tt1 << endl;

        return search(1, 100000, nums);
    }
};
