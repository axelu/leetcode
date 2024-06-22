
// 3046. Split the Array
// https://leetcode.com/problems/split-the-array/




class Solution {
public:
    bool isPossibleToSplit(vector<int>& nums) {
        int n = nums.size(); // n % 2 == 0; 1 <= nums[i] <= 100

        int cnt[101];memset(cnt,0,sizeof cnt);
        for(int i: nums) {
            ++cnt[i];
            if( cnt[i] == 3 )
                return false;
        }

        return true;
    }
};
