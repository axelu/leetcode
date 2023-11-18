
// 2732. Find a Good Subset of the Matrix
// https://leetcode.com/problems/find-a-good-subset-of-the-matrix/


/*  example
 *  bit  43210
 *  a    00010
 *       00001
 *       00100
 *  any number with the 1st bit not set
 */
class Solution {
    vector<int> countSetBits(int i) {
        vector<int> ret;
        int k = 0;
        while (i) {
            if( i & 1 )
                ret.push_back(k);
            i >>= 1;
            ++k;
        }
        return ret;
    }

public:
    vector<int> goodSubsetofBinaryMatrix(vector<vector<int>>& grid) {
        int m = grid.size();    // rows 1 <= m <= 10^4
        int n = grid[0].size(); // cols 1 <= n <= 5

        // worst case m = 10000, n = 5
        // that makes 30 possible non-empty subsets -> 300000 possibilities

        // let us view the columns as bits from right to left
        // there can only be 2^n

        map<int,int> mp; // val,row
        for(int i = 0; i < m; ++i) {
            int t = 0;
            for(int j = n-1; j >= 0; --j) {
                if( grid[i][j] == 1 ) {
                    t |= (1 << ((n-1) - j));
                }
            }
            if( t == 0 )
                return {i};
            mp[t] = i;
        }

        for(auto ito = mp.begin(); ito != mp.end(); ++ito) {
            int a = ito->first;
            for(auto iti = next(ito); iti != mp.end(); ++iti) {
                int b = iti->first;
                if( (a & b) == 0 ) {
                    return {min(ito->second,iti->second),max(ito->second,iti->second)};
                }
            }
        }

        return {};
    }
};
