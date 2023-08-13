
// 2810. Faulty Keyboard
// https://leetcode.com/problems/faulty-keyboard/



class Solution {
public:
    string finalString(string s) {
        // brute force

        int n = s.size();
        string ans = "";
        for(int i = 0; i < n; ++i) {
            if( s[i] == 'i' ) {
                reverse(ans.begin(),ans.end());
                continue;
            }
            ans.push_back(s[i]);
        }

        return ans;
    }
};
