
// 392. Is Subsequence
// https://leetcode.com/problems/is-subsequence/



class Solution {
private:
    bool isSubsequence(string& s, int& sn, int sIdx, string& t, int& tn, int tIdx) {
        if( sIdx == sn ) return true;

        for(int i = tIdx; i <= tn-(sn-sIdx); ++i) {
            if( t[i] != s[sIdx] ) continue;
            return isSubsequence(s,sn,sIdx+1,t,tn,i+1);
        }
        return false;
    }
public:
    bool isSubsequence(string& s, string& t) {
        int sn = s.size();
        int tn = t.size();
        if( sn > tn  ) return false;
        if( sn == tn ) return s == t;
        if( sn == 1  ) return t.find(s) != string::npos;

        return isSubsequence(s,sn,0,t,tn,0);
    }
};
