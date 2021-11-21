

// 2014. Longest Subsequence Repeated k Times
// https://leetcode.com/problems/longest-subsequence-repeated-k-times/





class Solution {
private:
    int N;

    string ans;

    bool occursKtimes(string& s, int pos, string& substring, int k) {
        // cout << "rec pos " << pos << " substring " << substring << endl;
        if( k == 0 )
            return true;

        // in order to fit the subsequence into s at least k times,
        // the subsequence has to be found by index imax
        int l = substring.size();
        int imax = N-1-(l*(k-1));

        // edge case
        if( l == 0 )
            return true;

        int t = 0;
        for(int i = pos; i <= imax; ++i) {
            if( s[i] == substring[t] ) {
                ++t;
                if( t == l ) { // we have reached the end of our subseqence
                    return occursKtimes(s,i+1,substring,k-1);
                }
            }
        }

        return false;
    }

    void rec(string& s, string substring, int k) {
        if( !occursKtimes(s,0,substring,k) )
            return;

        if( substring.size() >= ans.size() && substring > ans )
            ans = substring; // we have a better answer

        // greedily create subsequences
        char c;
        for(int i = 0; i < 26; ++i) {
            c = i+'a';
            rec(s,substring+c,k);
        }
    }




public:
    string longestSubsequenceRepeatedK(string s, int k) {
        N = s.size();

        // max length of subsequence
        // because of the relation between k and n,
        // the subsequence cannot be longer than 7 chars
        // maxLength = N/k;

        // cout << "N " << N << " maxLength " << maxLength << endl;

        ans = "";
        string ss = "";
        rec(s,ss,k);

        return ans;
    }
};
