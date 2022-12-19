
// 2278. Percentage of Letter in String
// https://leetcode.com/problems/percentage-of-letter-in-string/



class Solution {
public:
    int percentageLetter(string s, char letter) {
        int n = s.size();
        double cnt = 0;
        for(int i = 0; i < n; ++i)
            if( s[i] == letter )
                cnt += 1;

        return floor(cnt/n*100);
    }
};
