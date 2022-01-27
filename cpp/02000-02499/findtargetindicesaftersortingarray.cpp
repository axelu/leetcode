
// 2089. Find Target Indices After Sorting Array
// https://leetcode.com/problems/find-target-indices-after-sorting-array/


class Solution {
public:
    vector<int> targetIndices(vector<int>& nums, int target) {
        sort(nums.begin(),nums.end());

        int n = nums.size();

        // binary search lower bound while loop
        int s = 0;
        int e = n;
        int mid;
        while(s < e) {
            mid = s + ((e-s)/2);
            if( target <= nums[mid] )
                e = mid;
            else
                s = mid+1;
        }
        if( s < n && nums[s] < target )
            ++s;


        if( s == n || nums[s] > target ) // target not in nums
            return {};

        int l = s; // leftmost index of target


        // binary search upper bound while loop
        s = 0;
        e = n;
        while(s < e) {
            mid = s + ((e-s)/2);
            if( target >= nums[mid] )
                s = mid + 1;
            else
                e = mid;
        }
        if( s < n && nums[s] <= target )
            ++s;


        int r = s-1; // rightmost index of target


        vector<int> ans(r-l+1);
        for(int i = 0; i < r-l+1; ++i)
            ans[i] = i+l;

        return ans;
    }
};
