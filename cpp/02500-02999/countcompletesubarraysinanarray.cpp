
// 2799. Count Complete Subarrays in an Array
// https://leetcode.com/problems/count-complete-subarrays-in-an-array/



class Solution {
public:
    int countCompleteSubarrays(vector<int>& nums) {
        // 1 <= nums.length <= 1000
        // 1 <= nums[i] <= 2000
        int n = nums.size();
        
        // number of distinct elements in the whole array
        int target = 0;
        int cnt[2001];memset(cnt,0,sizeof cnt);
        for(int x: nums) {
            ++cnt[x];
            if( cnt[x] == 1 )
                ++target;
        }
        // cout << "number of distinct elements in the whole array: " << target << endl;
        if( target == 1 )
            return n * (n + 1)/2;
        
        // sliding window
        // expand the window till target unique elements
        //    we count the current subarray + all subarrays till the end of array
        // then shrlink the windwo till no longer target
        // then expand the window again till target unique elements
        //    we count the current subarray + all subarrays till the end of array
        // ans so on
        int ans = 0;
        memset(cnt,0,sizeof cnt);
        int unique = 0;
        int i = 0;
        for(int j = 0; j < n; ++j) {
            ++cnt[nums[j]];
            if( cnt[nums[j]] == 1 )
                ++unique;
            if( unique == target ) {
                int i_org = i;
                while( unique == target ) {
                    --cnt[nums[i]];
                    if( cnt[nums[i]] == 0 )
                        --unique;
                    ++i;
                }
                // we can count the following subarrays:
                // {[i_org,j], [i_org,j+1], ..., [i_org,n-1], 
                //  [i_org+1,j], [i_org+1,j+1], ..., [i_org+1,n-1],
                //  ...,
                //  [i-1,j], [i-1,j+1], ..., [i-1,n-1]}
                int t = n - j;      // tail factor
                int f = i - i_org;  // front factor
                ans += f * t;
            }
        }
        
        return ans;
    }
};
