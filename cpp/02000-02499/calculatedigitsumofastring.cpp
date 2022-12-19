
// 2243. Calculate Digit Sum of a String
// https://leetcode.com/problems/calculate-digit-sum-of-a-string/



class Solution {
public:
    string digitSum(string s, int k) {

        while( s.size() > k ) {

            string t = "";
            int cnt = 0;
            int sum = 0;
            for(int i = 0; i < s.size(); ++i) {
                 sum += s[i]-'0';
                ++cnt;
                if( cnt == k ) {
                    t = t + to_string(sum);
                    cnt = 0;
                    sum = 0;
                }
            }
            // finish up
            if( cnt > 0 )
                t = t + to_string(sum);

            s = t;
        }

        return s;
    }
};
