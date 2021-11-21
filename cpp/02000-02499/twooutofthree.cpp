
// 2032. Two Out of Three
// https://leetcode.com/problems/two-out-of-three/




class Solution {
public:
    vector<int> twoOutOfThree(vector<int>& nums1, vector<int>& nums2, vector<int>& nums3) {
        int cnt[101][3];memset(cnt,0,sizeof cnt);
        for(int i : nums1 )
            cnt[i][0] = 1;
        for(int i : nums2 )
            cnt[i][1] = 1;
        for(int i : nums3 )
            cnt[i][2] = 1;

        vector<int> ans;
        for(int i = 1; i < 101; ++i)
            if( cnt[i][0] + cnt[i][1] + cnt[i][2] >= 2 )
                ans.push_back(i);

        return ans;
    }
};
