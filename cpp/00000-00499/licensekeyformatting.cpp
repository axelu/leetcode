
// 482. License Key Formatting
// https://leetcode.com/problems/license-key-formatting/


class Solution {
private:
    void trim(string& S) {
        // trim leading dashes, if any
        while(S.front() == '-' )
            S.erase(0,1);
        // trim trailing dashes, if any
        while(S.back() == '-' )
            S.pop_back();
    }
public:
    string licenseKeyFormatting(string& S, int K) {
        trim(S);
        string ans = "";
        int j;
        for(int i = S.size()-1; i >= 0; --i) {
            if( S[i] != '-' ) {
                ans.insert(ans.begin(),toupper(S[i]));
                ++j;
                if( i > 0 && j == K ) {
                    ans.insert(ans.begin(),'-');
                    j = 0;
                }
            }
        }
        return ans;
    }
};
