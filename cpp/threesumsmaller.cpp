
// 259. 3Sum Smaller
// https://leetcode.com/problems/3sum-smaller/




class Solution {
private:
    // binary search largest element less than target
    int search(vector<int>& nums, int s, int e, int target) {
        if( s > e )
            return -1;

        int mid = s + ((e-s)/2);
        if( nums[mid] < target ) {
            // can we do better?
            int ans = search(nums,mid+1,e,target);
            return ans != -1 ? ans : mid;
        } else {
            return search(nums,s,mid-1,target);
        }
    }

public:
    int threeSumSmaller(vector<int>& nums, int target) {
        int n = nums.size();
        if( n < 3 )
            return 0;
        if( n == 3 )
            return nums[0]+nums[1]+nums[2]<target;

        sort(nums.begin(),nums.end());

        int ans = 0;

        int t,x,p;
        for(int i = 0; i < n-2; ++i) {
            for(int j = i+1; j < n-1; ++j) {

                t = nums[i]+nums[j];
                if( t == target && nums[j+1] >= 0 )
                    break;

                x = target - t;

                p = search(nums,j+1,n-1,x);
                if( p != -1 ) {

                    ans += p-j;


                }
            }
        }

        return ans;
    }
};
