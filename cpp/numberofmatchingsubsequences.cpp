
// 792. Number of Matching Subsequences
// https://leetcode.com/problems/number-of-matching-subsequences/



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
    int numMatchingSubseq(string& S, vector<string>& words) {
        int n = words.size();
        if( n == 0 ) return 0;

        unordered_map<string,int> mem;
        unordered_map<string,int>::iterator f;
        int ans = 0;
        int Sn = S.size();
        int sn;
        for(int i = 0; i < n; ++i) {
            f = mem.find(words[i]);
            if( f == mem.end() ) {
                sn = words[i].size();
                if( sn > Sn  ) {
                    f = mem.insert({words[i],0}).first;
                } else if( sn == Sn ) {
                    if( words[i] == S )
                        f = mem.insert({words[i],1}).first;
                    else
                        f = mem.insert({words[i],0}).first;
                } else if( sn == 1  ) {
                    if( S.find(words[i]) != string::npos )
                        f = mem.insert({words[i],1}).first;
                    else
                        f = mem.insert({words[i],0}).first;
                } else {
                    if( isSubsequence(words[i],sn,0,S,Sn,0) )
                        f = mem.insert({words[i],1}).first;
                    else
                        f = mem.insert({words[i],0}).first;
                }
            }
            ans += f->second;
        }
        return ans;
    }
};
