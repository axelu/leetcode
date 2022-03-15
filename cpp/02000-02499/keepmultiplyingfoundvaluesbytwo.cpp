
// 2154. Keep Multiplying Found Values by Two
// https://leetcode.com/problems/keep-multiplying-found-values-by-two/


class Solution {
public:
    int findFinalValue(vector<int>& nums, int original) {
        int cnt[1001];memset(cnt,0,sizeof cnt);
        for(int i : nums)
            ++cnt[i];

        while(original <= 1000 && cnt[original]) {
            --cnt[original];
            original *= 2;
        }

        return original;
    }
};
