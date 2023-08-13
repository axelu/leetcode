
// 2616. Minimize the Maximum Difference of Pairs
// https://leetcode.com/problems/minimize-the-maximum-difference-of-pairs/



class Solution {
private:
    int solve(vector<int>& nums, int n, int threshold) {
        int ret = 0;

        for(int i = 1; i < n; ++i) {
            if( nums[i] - nums[i-1] <= threshold ) {
                ++ret;
                ++i;
            }
        }

        return ret;
    }

    // binary search
    int search(vector<int>& nums, int n, int s, int e, int p) {
        if( s > e )
            return -1;

        int mid = s + ((e-s)/2);
        if( solve(nums,n,mid) >= p ) {
            // can we do better?
            int t = search(nums,n,s,mid-1,p);
            return t != -1 ? t : mid;
        }
        return search(nums,n,mid+1,e,p);
    }

public:
    int minimizeMax(vector<int>& nums, int p) {
        if( p == 0 )
            return 0;

        int n = nums.size();

        // we know the answer is somewhere between [0, maxdiff] inclusive
        sort(nums.begin(),nums.end());
        int s = 0;
        int e = nums[n-1] - nums[0];

        return search(nums,n,s,e,p);
    }
};
