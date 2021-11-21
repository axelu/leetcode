
// 31. Next Permutation
// https://leetcode.com/problems/next-permutation/

class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        size_t n = nums.size(); // 1 <= nums.length <= 100
        if( n == 1 )
            return;
        if( n == 2 ) {
            iter_swap(begin(nums),next(begin(nums)));
            return;
        }

        /*
        // sorted in non-descending order?
        if( is_sorted(begin(nums),end(nums)) ) {
            iter_swap(begin(nums) + n-2, begin(nums) + n-1);
            return;
        }
        // sorted in descending order?
        auto cmp = [](const int& a, const int& b){return a > b;};
        if( is_sorted(begin(nums),end(nums),cmp) ) {
            //sort(begin(nums),end(nums));
            for(int i = 0; i < n/2; ++i)
               iter_swap(begin(nums)+i,begin(nums)+n-1-i);
            return;
        }
        */

        int i = n-1, j = n-1;
        // find 1st instance from back where nums[i-1] < nums[i]
        for(; i > 0; --i)
            if( nums[i-1] < nums[i] ) break;
        if( i == 0 ) {
            // nums is in descending order
            for(; i < n/2; ++i)
               iter_swap(begin(nums)+i,begin(nums)+n-1-i);
            return;
        }
        // find 1st number nums[j] from back that is greater than nums[i-1]
        for(; j >= i; --j)
            if( nums[j] > nums[i-1] ) break;
        // swap nums[i-1] and nums[j]
        iter_swap(begin(nums)+i-1,begin(nums)+j);
        // reverse (nums[i],nums[n-1])
        int k = (n-i)/2;
        for(int l = 0; l < k; ++l) {
           iter_swap(begin(nums)+i+l,begin(nums)+n-1-l);
        }

    }
};
