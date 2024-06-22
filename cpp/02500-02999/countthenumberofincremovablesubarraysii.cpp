
// 2972. Count the Number of Incremovable Subarrays II
// https://leetcode.com/problems/count-the-number-of-incremovable-subarrays-ii/





class Solution {
public:
    long long incremovableSubarrayCount(vector<int>& nums) {
        int nums_sz = nums.size(); // 1 <= nums.length <= 100000
        if( nums_sz == 1L )
            return 1;

        // prefix
        int mem_prefix[100000];
        mem_prefix[0] = 1;
        int increasing_up_to_idx = 0;
        for(int i = 1; i < nums_sz; ++i) {
            if( mem_prefix[i-1] == 0 ) {
                mem_prefix[i] = 0;
            } else if( nums[i-1] < nums[i] ) {
                mem_prefix[i] = 1;
                increasing_up_to_idx = i;
            } else {
                mem_prefix[i] = 0;
            }
        }
        // cout << "increasing_up_to_idx " << increasing_up_to_idx << endl;

        // suffix
        int mem_suffix[100000];
        mem_suffix[nums_sz-1] = 1;
        int decreasing_down_to_idx = nums_sz-1;
        for(int i = nums_sz-2; i >= 0; --i) {
            if( mem_suffix[i+1] == 0 ) {
                mem_suffix[i] = 0;
            } else if( nums[i] < nums[i+1] ) {
                mem_suffix[i] = 1;
                decreasing_down_to_idx = i;
            } else {
                mem_suffix[i] = 0;
            }
        }
        // cout << "decreasing_down_to_idx " << decreasing_down_to_idx << endl;

        // suffix only aka remove prefix
        // we can remove all subarrays [0,j] where max(0,decreasing_down_to_idx - 1) <= j <= n-2
        long suffix = (nums_sz-1) - (max(0, decreasing_down_to_idx - 1));
        // cout << "suffix " << suffix << endl;

        // remove a subarray[i,j] with 0 < i <= n-2 and 0 < j <= n-2
        long middle = 0;
        for(int i = 1; i <= min(increasing_up_to_idx + 1, nums_sz - 2); ++i) {

            // we know that nums is strictly increasing in range[decreasing_down_to_idx,nums_sz-1]
            // so we can do a binary search for j in range range[decreasing_down_to_idx,nums_sz-2] where nums[j] > nums[i]
            // aka upper bound

            // returns 'n' if nums[n-1] <= target
            // returns  0  if nums[0] > target
            // binary search upper bound while loop
            // upper bound -> greater than target
            int s = max(decreasing_down_to_idx, i + 1);
            int n = nums_sz;
            int e = n;
            int mid;
            int target = nums[i-1];
            while(s < e) {
                mid = s + ((e-s)/2);
                if( target >= nums[mid] )
                    s = mid + 1;
                else
                    e = mid;
            }
            if( s < n && nums[s] <= target )
                ++s;

            // cout << "i " << i << " s " << s << " we can remove " << nums_sz - s << endl;

            if( s < n ) {
                middle += (long)nums_sz - (long)s;
            } else {
                break;
            }
        }
        // cout << "middle " << middle << endl;

        // prefix only aka remove suffix
        long prefix = min(nums_sz-1, increasing_up_to_idx + 1);
        // cout << "prefix " << prefix << endl;

        return 1L + suffix + middle + prefix; // plus 1 because removing all is an option
    }
};
