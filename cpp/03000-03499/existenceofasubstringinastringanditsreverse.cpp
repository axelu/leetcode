
// 3083. Existence of a Substring in a String and Its Reverse
// https://leetcode.com/problems/existence-of-a-substring-in-a-string-and-its-reverse/



class Solution {
public:
    bool isSubstringPresent(string s) {
        int n = s.size();
        if( n == 1 )
            return false;

        set<string> st;

        // left to right
        for(int i = 0; i < n-1; ++i) {
            string t(1,s[i]);
            t = t + s[i+1];
            st.insert(t);
        }
        // right to left
        for(int i = n-1; i > 0; --i) {
            string t(1,s[i]);
            t = t + s[i-1];
            if( st.count(t) )
                return true;
        }

        return false;
    }
};
