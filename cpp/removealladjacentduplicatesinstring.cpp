
// 1047. Remove All Adjacent Duplicates In String
// https://leetcode.com/problems/remove-all-adjacent-duplicates-in-string/


class Solution {
public:
    string removeDuplicates(string& S) {
        size_t n = S.size();
        if( n == 1 ) return S;

        stack<char> stck;
        stck.push(S[0]);
        for(int i = 1; i < n; ++i) {
            if( !stck.empty() ) {
                if( S[i] != stck.top() ) {
                    stck.push(S[i]);
                } else {
                    stck.pop();
                }
            } else {
                stck.push(S[i]);
            }
        }

        string r = "";
        while(!stck.empty()) {
            r = stck.top() + r;
            stck.pop();
        }

        return r;
    }
};
