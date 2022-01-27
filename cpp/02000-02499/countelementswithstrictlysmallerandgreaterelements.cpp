
// 2148. Count Elements With Strictly Smaller and Greater Elements 
// https://leetcode.com/problems/count-elements-with-strictly-smaller-and-greater-elements/



class Solution {
public:
    int countElements(vector<int>& nums) {
        if( nums.size() < 3 )
            return 0;

        int cnt[200001];memset(cnt,0,sizeof cnt);
        for(int i : nums)
            ++cnt[i+100000];

        int ans = 0;
        int mn = 200001;
        int mx = 0;
        int mxcnt = 0;
        for(int i = 0; i < 200001; ++i)
            if( cnt[i] != 0 ) {
                if( i < mn )
                    mn = i;
                if( i > mn )
                    ans += cnt[i];
                mxcnt = cnt[i];
            }

        return ans > 0 ? ans-mxcnt : 0;
    }
};
