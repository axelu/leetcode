
// 3407. Substring Matching Pattern
// https://leetcode.com/problems/substring-matching-pattern/





class Solution {
public:
    bool hasMatch(string s, string p) {
        int s_sz = s.size();
        int p_sz = p.size();

        // it is guaranteed that p contains exactly one '*'

        if( p_sz > s_sz + 1 )
            return false;

        int asterisk_idx = p.find('*');

        if( p_sz == s_sz + 1 ) {
            p.erase(asterisk_idx, 1);
            return s == p;
        }

        if( p_sz == 1 )
            return true;

        // p_sz > 1
        // our asterisk in p could be in the front, back or somewhere in the middle
        if( p[0] == '*' || p[p_sz-1] == '*' ) {
            if( p[0] == '*' )
                p.erase(0,1);
            else
                p.pop_back();
            return s.find(p) != string::npos;
        }

        int a = s.find(p.substr(0,asterisk_idx));
        if( a == string::npos )
            return false;

        int b = s.find(p.substr(asterisk_idx+1), a + asterisk_idx);
         if( b == string::npos )
            return false;

        return true;
    }
};
