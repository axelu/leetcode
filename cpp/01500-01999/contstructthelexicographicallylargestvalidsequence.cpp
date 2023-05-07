
// 1718. Construct the Lexicographically Largest Valid Sequence
// https://leetcode.com/problems/construct-the-lexicographically-largest-valid-sequence/



class Solution {
private:
    bool rec(int i, vector<int>& ans, int n, int sequence) {
        if( sequence == 0 )
            return true;

        if( ans[i] != -1 )
            return rec(i+1,ans,n,sequence);

        // greedily try placing the largest number possible at i in answer
        for(int k = n; k > 0; --k) {
            if( !((sequence >> k) & 1) )
                continue;

            sequence &= ~(1 << k);

            if( k == 1 ) {
                ans[i] = k;
                if( rec(i+1,ans,n,sequence) )
                    return true;

                // backtrack
                ans[i] = -1;

            } else if( i+k < 2*n-1 && ans[i+k] == -1 ) {
                ans[i] = k;
                ans[i+k] = k;
                if( rec(i+1,ans,n,sequence) )
                    return true;

                // backtrack
                ans[i+k] = -1;
                ans[i] = -1;
            }

            // backtrack
            sequence |= 1 << k;
        }

        return false;
    }

public:
    vector<int> constructDistancedSequence(int n) {
        int sequence = 0;
        for(int i = 1; i <= n; ++i)
            sequence |= 1 << i;

        vector<int> ans(2*n-1,-1);

        rec(0,ans,n,sequence);

        return ans;
    }
};
