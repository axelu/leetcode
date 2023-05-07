
// 2274. Maximum Consecutive Floors Without Special Floors
// https://leetcode.com/problems/maximum-consecutive-floors-without-special-floors/




class Solution {
public:
    int maxConsecutive(int bottom, int top, vector<int>& special) {

        sort(special.begin(),special.end());

        int ans = 0;

        ans = max(ans,special[0] - bottom);
        for(int i = 1; i < special.size(); ++i)
            ans = max(ans, special[i] - special[i-1] - 1);
        ans = max(ans,top - special.back());

        return ans;
    }
};
