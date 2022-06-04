
// 484. Find Permutation
// https://leetcode.com/problems/find-permutation/



class Solution {
public:
    vector<int> findPermutation(string s) {
        int n = s.size(); // our permutation is n+1 in length

        // e.g. n = 5, our permutation is 1-6
        // "IDDII" -> 1,4,3,2,5,6
        //  0 1 2 3 4 5 index
        //  I D D I I
        //  1 4 3 2 5 6
        //  0 2 0 0 0 0 dr
        // "IDDDD" -> 1,6,5,4,3,2
        //  0 1 2 3 4 5 index
        //  I D D D D
        //  1 6 5 4 3 2
        //  0 4 0 0 0 0 dr
        // "DDDDD" -> 6,5,4,3,2,1
        //  0 1 2 3 4 5 index
        //  D D D D D
        //  6 5 4 3 2 1
        //  5 0 0 0 0 0 dr

        // in order to optimally, in our case lexicographically smallest,
        // distribute integers 1 to n+1 inclusive, we need to know
        // in advance local peaks and the lenght of decreasing runs (left to right)
        // in order to know that, we will record the lenght of decreasing runs
        // while investigating the string right to left

        int dr[n+1];memset(dr,0,sizeof dr); // length of decreasing run starting at i (not including i)
        dr[n] = 0;
        int l = 0; // length of current decreasing run
        for(int i = n-1; i >= 0; --i) {
            if( s[i] == 'D' ) {
                ++l;
            } else if( l > 0 ) { // prior was a local peak
                dr[i+1] = l;
                l = 0;
            }
        }
        if( l > 0 )
            dr[0] = l;

        vector<int> ans(n+1);
        int nxt = 1; // initially our next integer to distribute is 1
        int t;
        for(int i = 0; i <= n; ++i) {
            if( dr[i] != 0 ) {
                t = dr[i];
                for(int k = t; k >= 0; --k,++i)
                    ans[i] = nxt + k;
                --i; // loop will advance i
                nxt += t + 1;
            } else {
                ans[i] = nxt;
                ++nxt;
            }
        }

        return ans;
    }
};
