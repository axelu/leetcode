
// 1016. Binary String With Substrings Representing 1 To N
// https://leetcode.com/problems/binary-string-with-substrings-representing-1-to-n/



class Solution {
public:
    bool queryString(string s, int n) {
        int s_sz = s.size();

        unordered_set<int> us;

        // brute force
        for(int i = s_sz - 1; i >= 0; --i) {
            int x = 0;
            for(int j = i, k = 0; j >= 0 && k <= 30; --j,++k) {
                if( s[j] == '1' )
                    x |= 1 << k;
                // cout << "i " << i << " j " << j << " x " << x << endl;
                if( x > 0 && x <= n )
                    us.insert(x);
            }
        }

        return us.size() == n;
    }
};
