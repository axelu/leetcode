
// 1910. Remove All Occurrences of a Substring
// https://leetcode.com/problems/remove-all-occurrences-of-a-substring/





class Solution {
public:
    string removeOccurrences(string s, string part) {
        int sn = s.size();
        int pn = part.size();

        string t = "";

        if( pn == 1 ) {
            for(int i = 0; i < sn; ++i)
                if( s[i] != part[0] )
                    t.push_back(s[i]);
            return t;
        }

        if( sn == pn )
            return s == part ? t : s;

        if( sn < pn )
            return s;


        string stck = "";
        t.reserve(pn);
        for(int i = 0; i < sn; ++i) {
            t.push_back(s[i]);
            if( t.size() < pn )
                continue;

            if( t == part ) {
                t.clear();
                for(int j = 0; j < pn-1 && stck.size() > 0; ++j) {
                    t.insert(0,1,stck.back());
                    stck.pop_back();
                }
            } else {
                stck.push_back(t[0]);
                t.erase(0,1);
            }
        }

        return stck+t;
    }
};
