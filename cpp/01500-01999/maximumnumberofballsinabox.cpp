
// 1742. Maximum Number of Balls in a Box
// https://leetcode.com/problems/maximum-number-of-balls-in-a-box/


class Solution {
public:
    int countBalls(int lowLimit, int highLimit) {
        // 1 <= lowLimit <= highLimit <= 10^5
        int cnt[46]; memset(cnt,0,sizeof cnt);

        int x,sum,ans=0;
        for(int i = lowLimit; i <= highLimit; ++i) {
            x = i;
            sum = 0;
            while(x>0) {
                sum += x%10;
                x /= 10;
            }
            ++cnt[sum];
            ans = max(ans,cnt[sum]);
        }
        return ans;
    }
};
