
// 3581. Count Odd Letters from Number
// https://leetcode.com/problems/count-odd-letters-from-number/




class Solution {
public:
    int countOddLetters(int n) {
        unordered_map<char,string> um;
        um['0'] = "zero";
        um['1'] = "one";
        um['2'] = "two";
        um['3'] = "three";
        um['4'] = "four";
        um['5'] = "five";
        um['6'] = "six";
        um['7'] = "seven";
        um['8'] = "eight";
        um['9'] = "nine";

        int cnt[26];memset(cnt,0,sizeof cnt);
        string s = to_string(n);
        for(char c: s) {
            for(char chr: um[c])
                ++cnt[chr-'a'];
        }

        int ans = 0;
        for(int i = 0; i < 26; ++i)
            if( cnt[i] % 2  )
                ++ans;

        return ans;
    }
};
