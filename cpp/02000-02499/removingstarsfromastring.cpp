
// 2390. Removing Stars From a String
// https://leetcode.com/problems/removing-stars-from-a-string/



class Solution {
public:
    string removeStars(string& s) {
        stack<char> stck;

        for(char c: s)
            if( c == '*' )
                stck.pop();
            else
                stck.push(c);

        s = "";
        while( !stck.empty() ) {
            s.push_back(stck.top());
            stck.pop();
        }

        reverse(s.begin(),s.end());
        return s;
    }
};
