
// 1461. Check If a String Contains All Binary Codes of Size K
// https://leetcode.com/problems/check-if-a-string-contains-all-binary-codes-of-size-k/




class Solution {
public:
    bool hasAllCodes(string s, int k) {
        int n = s.size();
        if( n - k < 0 ) return false;
        int stsz = pow(2,k);
        if( n - k + 1 < stsz) return false;
        unordered_set<string> st(stsz);
        for(int i = 0; i <= n - k; ++i) {
            st.insert(s.substr(i,k));
            if( st.size() == stsz ) break;
        }

        return st.size() == stsz;
    }
};
