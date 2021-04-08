
// 161. One Edit Distance
// https://leetcode.com/problems/one-edit-distance/
// day 22 January 2021 Bonus question
// https://leetcode.com/explore/challenge/card/january-leetcoding-challenge-2021/582/week-4-january-22nd-january-28th/3612/



class Solution {
private:
    bool diff1(string& s, size_t& sn, string& t) {
            if( sn == 0 ) return true;
            int i = 0;
            for(; i < sn; ++i)
                if( s[i] != t[i] ) break;
            if( i == sn ) return true;
            for(; i < sn; ++i)
                if( s[i] != t[i+1] ) break;
            if( i == sn ) return true;
            return false;
    }
public:
    bool isOneEditDistance(string s, string t) {
        size_t sn = s.size();
        size_t tn = t.size();

        if( sn+1 == tn ) {
            return diff1(s,sn,t);
        } else if( sn-1 == tn ) {
            return diff1(t,tn,s);
        } else if( sn == tn ) {
            int i = 0;
            for(; i < sn; ++i)
                if( s[i] != t[i] ) break;
            if( i == sn ) return false;
            ++i;
            for(; i < sn; ++i)
                if( s[i] != t[i] ) break;
            if( i == sn ) return true;
        }
        return false;
    }
};
