
// 2856. Minimum Array Length After Pair Removals
// https://leetcode.com/problems/minimum-array-length-after-pair-removals/





class Solution {
private:
    bool solve(vector<int>& nums, int k) {
        int n = nums.size();
        for(int i = 0; i < k; ++i)
            if( nums[i] >= nums[n-k+i] )
                return false;
        return true;
    }

    // binary search
    int search(int s, int e, vector<int>& nums) {
        if( s > e )
            return -1;

        int mid = s + ((e-s)/2);
        bool f = solve(nums,mid);
        if( f ) {
            // can we do better?
            int t = search(mid+1,e,nums);
            return t != -1 ? t : mid;
        }
        return search(s,mid-1,nums);
    }


public:
    int minLengthAfterRemovals(vector<int>& nums) {
        // nums is in non-decreasing order
        // example
        // 0 1 2 3 4 5
        // 3 3 5 5 5 7
        // ---     ---
        // lets take the smallest k and largest k elements, as long as we can delete pairs
        // nums[i],nums[n-k+i]  with 0 <= i < k, we havea a solution
        int n = nums.size();
        int t = search(0,n/2,nums);
        return n - 2*t;
    }
};
