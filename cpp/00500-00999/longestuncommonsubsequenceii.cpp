
// 522. Longest Uncommon Subsequence II
// https://leetcode.com/problems/longest-uncommon-subsequence-ii/


// solution appoach 32
class Solution {
private:
    bool isSubsequence(string& a, string& b) {
        // is string a a subsequence of string b?
        int an = a.size();
        int bn = b.size();
        if( an > bn ) return false;
        if( a == b ) return true;

        int j = 0;
        for(int i = 0; i < bn && j < an; ++i)
            if( a[j] == b[i] )
                j++;
        return j == an;
    }

public:
    int findLUSlength(vector<string>& strs) {

        sort(strs.begin(),strs.end(),[](string& a, string& b){
            return a.size() > b.size();
        });

        int n = strs.size();
        int subSeq;
        for(int i = 0, j; i < n; ++i) {
            subSeq = true;
            for(j = 0; j < n; ++j) {
                if( i == j ) continue;
                if( isSubsequence(strs[i], strs[j]) ) {
                    subSeq = false;
                    break;
                }
            }
            if( subSeq ) return strs[i].length();
        }
        return -1;
    }
};
