
// 1072. Flip Columns For Maximum Number of Equal Rows
// https://leetcode.com/problems/flip-columns-for-maximum-number-of-equal-rows/




class Solution {
public:
    int maxEqualRowsAfterFlips(vector<vector<int>>& matrix) {
        int m = matrix.size();
        int n = matrix[0].size();

        // we need to count equal rows and count their oposites
        // the max count of row and its opposite is the answer

        bitset<300> bs;
        bitset<300> base;
        unordered_map<bitset<300>,int> row;
        unordered_map<bitset<300>,int> opp;

        // process row 0
        for(int j = 0; j < n; ++j) {
            base.set(j);
            if( matrix[0][j] )
                bs.set(j);
        }
        row.insert({bs,1});
        bs ^= base;
        opp.insert({bs,0});

        // process the remaining rows
        for(int i = 1; i < m; ++i) {
            bs.reset();

            for(int j = 0; j < n; ++j)
                if( matrix[i][j] )
                    bs.set(j);
            auto frow = row.find(bs);
            if( frow != row.end() ) {
                ++frow->second;
            } else {
                auto fopp = opp.find(bs);
                if( fopp != opp.end() ) {
                    ++fopp->second;
                } else {
                    row.insert({bs,1});
                    bs ^= base;
                    opp.insert({bs,0});
                }
            }
        }

        int ans = 0;

        for(auto it = row.begin(); it != row.end(); ++it) {
            int t = it->second;
            bs = it->first;
            bs ^= base;
            t += opp.find(bs)->second;

            ans = max(ans,t);
        }

        return ans;
    }
};
