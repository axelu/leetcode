
// 816. Ambiguous Coordinates
// https://leetcode.com/problems/ambiguous-coordinates/
// day 13 May 2021 challenge
// https://leetcode.com/explore/challenge/card/may-leetcoding-challenge-2021/599/week-2-may-8th-may-14th/3741/




class Solution {
private:
    vector<string> split(string& s, int l, int r) {
        if( l == r ) return {s.substr(l,1)};

        // cannot start with 0 and end with 0
        if( s[l] == '0' && s[r] == '0' ) return {};

        // ends with 0, then only one possibility
        if( s[r] == '0' ) return {s.substr(l,r-l+1)};

        vector<string> ret;
        if( s[l] != '0' ) ret.push_back(s.substr(l,r-l+1));

        // move the comma from left to right
        // we cannot cross two 0's
        string ls,rs;
        for(int i = l; i < r; ++i) {
            if( i-l+1 == 2 && s[i-1] == '0' )
                break;

            // left side
            ls = s.substr(l,i-l+1);
            // right side
            rs = s.substr(i+1,r-i);

            ret.push_back(ls+"."+rs);
        }

        return ret;
    }

public:
    vector<string> ambiguousCoordinates(string s) {
        // 4 <= s.length <= 12
        int n = s.size();

        vector<string> ans;
        vector<string> lft;
        vector<string> rgt;
        int j,k;
        string str;
        for(int i = 1; i < n-2; ++i) {
            lft.clear();rgt.clear();
            // left side
            lft = split(s,1,i);
            if( lft.empty() ) continue;
            // right side
            rgt = split(s,i+1,n-2);
            if( rgt.empty() ) continue;
            for(j = 0; j < lft.size(); ++j) {
                for(k = 0; k < rgt.size(); ++k) {
                    str = "(" + lft[j] + ", " + rgt[k] + ")";
                    ans.push_back(str);
                }
            }
        }
        return ans;
    }
};
