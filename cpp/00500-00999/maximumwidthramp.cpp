
// 962. Maximum Width Ramp
// https://leetcode.com/problems/maximum-width-ramp/



class Solution {
public:
    int maxWidthRamp(vector<int>& nums) {
        int n = nums.size(); // 2 <= nums.length <= 5 * 10^4
        
        // rephrasing the question:
        // when at a given index i, find the largest index j with i < j so that nums[i] <= nums[j]
        
        int ans = 0;
        
        map<int,int> mp;
        
        int mx_seen = nums[n-1];
        mp[nums[n-1]] = n-1;
        for(int i = n-2; i >= 0; --i) {
            int val = nums[i];
            if( val > mx_seen ) {
                mx_seen = val;
                mp[val] = i;

            } else {
                auto lb = mp.lower_bound(val);    
                ans = max(ans, lb->second - i);
            
            }
        }
        
        return ans;
    }
};
