
// 2264. Largest 3-Same-Digit Number in String
// https://leetcode.com/problems/largest-3-same-digit-number-in-string/



class Solution {
public:
    string largestGoodInteger(string num) {
        int n = num.size();

        string ans = "";

        string t = "";
        int k = 0;
        for(int i = 0; i < n; ++i)
            if( k == 0 ) {
                t = t + num[i];
                ++k;
            } else if( num[i] == num[i-1] ) {
                t = t + num[i];
                ++k;
                if( k == 3 ) {
                    if( t > ans )
                        ans = t;
                    t =  "";
                    k = 0;
                }
            } else {
                t = "";
                t = t + num[i];
                k = 1;
            }

        return ans;
    }
};
