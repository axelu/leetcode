
// 1957. Delete Characters to Make Fancy String
// https://leetcode.com/problems/delete-characters-to-make-fancy-string/





class Solution {
public:
    string makeFancyString(string& s) {
        int n = s.size();
        if( n < 3 )
            return s;

        string ans = "";
        char a = s[0];
        char b = s[1];
        char c;
        for(int i = 2; i < n; ++i) {
            c = s[i];
            if( a == b && a == c ) {
                // do nothing
            } else {
                ans.push_back(a);
            }
            a = b;
            b = c;
        }
        ans.push_back(s[n-2]);
        ans.push_back(s[n-1]);
        return ans;
    }
};
