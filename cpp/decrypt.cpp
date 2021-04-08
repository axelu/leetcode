
// 1652. Defuse the Bomb
// https://leetcode.com/problems/defuse-the-bomb/


class Solution {
public:
    vector<int> decrypt(vector<int>& code, int k) {
        auto n = code.size();
        vector<int> r(n);
        if( k == 0 ) return r;

        int s,p;
        for(int i = 0; i < n; ++i) {
            s = 0;
            if( k > 0 ) {
                for(int j = i+1; j <= i + k; ++j) {
                    p = j % n;
                    s += code[p];
                }
            } else {
                for(int j = i-1; j >= i + k; --j) {
                    p = j >= 0 ? j : n - (abs(j) % n);
                    s += code[p];
                }
            }
            r[i] = s;
        }

        return r;
    }
};
