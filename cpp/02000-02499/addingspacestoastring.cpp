
// 2109. Adding Spaces to a String
// https://leetcode.com/problems/adding-spaces-to-a-string/





class Solution {
public:
    string addSpaces(string& s, vector<int>& spaces) {
        int s_sz = s.size();
        int spaces_sz = spaces.size();

        string ans(s_sz+spaces_sz,' ');

        for(int i = 0, j = 0, ans_idx = 0; i < s_sz; ++i, ++ans_idx) {
            if( j < spaces_sz && i == spaces[j] ) {
                ++ans_idx;
                ++j;
            }
            ans[ans_idx] = s[i];
        }

        return ans;
    }
};




/*
// TLE
public:
    string addSpaces(string s, vector<int>& spaces) {

        auto it = s.begin();
        int pre = 0;
        for(int i = 0; i < spaces.size(); ++i) {
            int t = spaces[i] - pre;
            advance(it,t);
            it = s.insert(it,' ');
            ++it;
            pre = spaces[i];
        }

        return s;
    }
};
*/
