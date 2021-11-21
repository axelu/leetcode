
// 1358. Number of Substrings Containing All Three Characters
// https://leetcode.com/problems/number-of-substrings-containing-all-three-characters/



class Solution {
public:
    int numberOfSubstrings(string& s) {
        int n = s.size();

        vector<int> as; // idx of all a's
        vector<int> bs; // idx of all b's
        vector<int> cs; // idx of all c's

        int i;
        for(i = 0; i < n; ++i) {
            if( s[i] == 'a' ) as.push_back(i);
            else if( s[i] == 'b' ) bs.push_back(i);
            else cs.push_back(i);
        }

        int an = as.size(), bn = bs.size(), cn = cs.size();
        if( an == 0 || bn == 0 || cn == 0 )
            return 0;

        int ans = 0;
        int a = 0, b = 0, c = 0;
        for(i = 0; i < n-2; ++i) {
            if( s[i] == 'a' ) {
                ans += n - max(bs[b],cs[c]);
                ++a;
            } else if( s[i] == 'b' ) {
                ans += n - max(as[a],cs[c]);
                ++b;
            } else {
                ans += n - max(as[a],bs[b]);
                ++c;
            }
            if( a == an || b == bn || c == cn )
                break;
        }

        return ans;
    }
};
