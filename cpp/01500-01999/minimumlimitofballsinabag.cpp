
// 1760. Minimum Limit of Balls in a Bag
// https://leetcode.com/problems/minimum-limit-of-balls-in-a-bag/



class Solution {
private:
    bool solve(vector<int>& nums, int target, int maxOperations) {
        int n = nums.size();

        for(int i = 0; i < n; ++i) {
            if( nums[i] <= target )
                break;

            int t = nums[i] / target;
            if( nums[i] % target == 0 )
                --t;
            maxOperations -= t;
            if( maxOperations < 0 )
                return false;
        }

        return true;
    }

    // binary search
    int search(vector<int>& nums, int s, int e, int maxOperations) {
        if( s > e )
            return -1;

        int mid = s + ((e-s)/2);
        // can we reduce all elements in nums that are greater than mid
        // to mid in less or equal maxOperations number of operations
        bool f = solve(nums,mid,maxOperations);
        if( f ) {
            // can we do better?
            int t = search(nums,s,mid-1,maxOperations);
            return t != -1 ? t : mid;
        } else {
            return search(nums,mid+1,e,maxOperations);
        }
    }

public:
    int minimumSize(vector<int>& nums, int maxOperations) {
        sort(nums.begin(),nums.end(),greater<int>());
        int mx = nums[0];
        int n  = nums.size();
        if( maxOperations == 1 ) {
            // we can split the largest element in half
            int t = mx/2;
            if( mx % 2 )
                ++t;
            return n == 1 ? t : max(t,nums[1]);
        }


        // our answer is between 1 and max(nums[i]) where 0 <= i < n
        return search(nums,1,mx,maxOperations);
    }
};
