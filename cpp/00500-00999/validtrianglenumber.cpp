
// 611. Valid Triangle Number
// https://leetcode.com/problems/valid-triangle-number/
// day 15 July 2021 challenge
// https://leetcode.com/explore/challenge/card/july-leetcoding-challenge-2021/610/week-3-july-15th-july-21st/3815/



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
    int triangleNumber(vector<int>& nums) {
        int n = nums.size();
        if( n < 3 )
            return 0;

        int ans = 0;


        // three sides of a triangle a,b,c
        // valid if 0 < a,b,c and c < a+b
        int s = 0,a,b,t,t_max = -1;
        sort(begin(nums),end(nums));
        for(int i = 0; i < n-2; ++i) {
            if( nums[i] == 0 ) {
                continue;
                s = i+1;
            }
            a = nums[i];
            for(int j = i+1; j < n-1; ++j) {
                b = nums[j];
                // c in nums in range [s,n-1]
                t = search(nums,s,n-1,a+b);
                if( t != -1 && t > t_max ) { // only if we discovered new c's
                    ans += t-j;
                    t = t_max;
                }
            }
        }

        return ans;
    }
};
