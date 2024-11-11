
// 3290. Maximum Multiplication Score
// https://leetcode.com/problems/maximum-multiplication-score/





class Solution {
private:

    long long mem[4][100000];

    long long rec(const vector<int>& a, const int posa, const vector<int>& b, const int b_sz, const int posb) {
        if( posa == 4 )
            return 0LL;

        if( mem[posa][posb] != LLONG_MIN )
            return mem[posa][posb];

        // we have a choice
        //    don't skip OR
        //    skip if we can

        long long x = ((long long)a[posa] * b[posb]) + rec(a, posa + 1, b, b_sz, posb + 1);

        long long y = LLONG_MIN;
        if( b_sz - posb > 4 - posa )
            y = rec(a, posa, b, b_sz, posb + 1);

        return mem[posa][posb] = max(x, y);
    }



public:
    long long maxScore(vector<int>& a, vector<int>& b) {
        // a.length == 4
        int b_sz = b.size();

        for(int i = 0; i < 4; ++i)
            for(int j = 0; j < b_sz; ++j)
                mem[i][j] = LLONG_MIN;

        return rec(a, 0, b, b_sz, 0);
    }
};
