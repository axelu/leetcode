
// 2009. Minimum Number of Operations to Make Array Continuous
// https://leetcode.com/problems/minimum-number-of-operations-to-make-array-continuous/





class Solution {
private:

    // binary search lower bound
    int search(vector<int>& nums, int s, int e, int target) {
        // nums can have duplicates!
        // if target exists return the smallest index of target
        // if target doesn't exist return the
        // smallest index of the next larger element

        if( s > e )
            return -1;

        int mid = s + ((e-s)/2);
        if( nums[mid] == target ) {
            // can we do better?
            int t = search(nums,s,mid-1,target);
            return t != -1 ? t : mid;
        } else if( nums[mid] < target ) {
            return search(nums,mid+1,e,target);
        } else {
            // nums[mid] > target
            // can we do better?
            int t = search(nums,s,mid-1,target);
            return t != -1 ? t : mid;
        }
    }


public:
    int minOperations(vector<int>& nums) {
        int n = nums.size();
        if( n == 1 )
            return 0;

        int ans = INT_MAX;

        sort(begin(nums),end(nums));

        // prefixsum to count duplicates
        // in a certain range quickly
        int pfxDupCount[n];
        pfxDupCount[0] = 0;
        for(int i = 1; i < n; ++i)
            if( nums[i-1] == nums[i] )
                pfxDupCount[i] = pfxDupCount[i-1]+1;
            else
                pfxDupCount[i] = pfxDupCount[i-1];



        // binary search to get the possible
        // right end of the window and calculate
        // the possible answer
        int endValue,t,k,jmax,j;
        for(int i = 0; i < n; ++i) {

            endValue = nums[i]+n-1;
            t = search(nums,i+1,n-1,endValue);

            // we know everything to the left of i will need to change
            // plus
            // if t == -1, then we know everything to the right of i
            //             is smaller than endValue
            //             duplicates between inclusive i+1 and n-1 need change
            // if t != -1 and nums[t] == endValue, then we know
            //             everything to the right of t will need to change
            //             and any duplicates between inclusive i+1 and t-1
            // if t != -1 and nums[t] > endValue, then we know
            //             t and everything to the right of t will need to change
            //             and any duplicates between inclusive i+1 and t-1


            k = i; // number changes to the left of i
            if( t == -1 ) {
                jmax = n;
            } else {
                k += nums[t] == endValue ? n-1-t : n-t; // changes to the right of t
                jmax = t;
            }

            // changes in between inclusive
            k += pfxDupCount[jmax-1]-pfxDupCount[i];

            ans = min(ans,k);
        }

        return ans;
    }
};
