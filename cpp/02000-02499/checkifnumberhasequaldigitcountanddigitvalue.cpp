
// 2283. Check if Number Has Equal Digit Count and Digit Value
// https://leetcode.com/problems/check-if-number-has-equal-digit-count-and-digit-value/




class Solution {
public:
    bool digitCount(string num) {
        int n = num.size();
        int cnt[10];memset(cnt,0,sizeof cnt); // cnt
        for(int i = 0; i < n; ++i)
            ++cnt[num[i]-'0'];

        for(int i = 0; i < n; ++i)
            if( cnt[i] != num[i]-'0' )
                return false;

        return true;
    }
};
