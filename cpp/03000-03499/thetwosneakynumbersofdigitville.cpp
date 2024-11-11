
// 3289. The Two Sneaky Numbers of Digitville
// https://leetcode.com/problems/the-two-sneaky-numbers-of-digitville/




class Solution {
public:
    vector<int> getSneakyNumbers(vector<int>& nums) {
        int nplus2 = nums.size();
        int n = nplus2 - 2;

        // 0 <= nums[i] < n
        // The input is generated such that nums contains exactly two repeated elements.

        int cnt[n]; memset(cnt,0,sizeof cnt);
        vector<int> ans;
        for(int x: nums) {
            ++cnt[x];
            if( cnt[x] == 2 )
                ans.push_back(x);
        }



        return ans;
    }
};
