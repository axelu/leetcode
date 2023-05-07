
// 1247. Minimum Swaps to Make Strings Equal
// https://leetcode.com/problems/minimum-swaps-to-make-strings-equal/




class Solution {
public:
    int minimumSwap(string s1, string s2) {
        // each string s1 and s2 will have some number of of 'x' and/or 'y' possibly 0
        // let x1 and x2 be number of 'x' in s1 and s2 respectively
        // let y1 and y2 be number of 'y' in s1 and s2 respectively
        // for there to be a solution, x1+x2 and y1+y2 must be even

        int n = s1.size(); // s1.size() == s2.size()
        //cout << "n " << n << endl;

        int ans = 0;

        int i = 0;
        int r = 0;
        while( i < n && r < 2 ) {
            char c1 = s1[i];
            char c2 = s2[i];

            if( c1 == c2 ) {
                ++i;

            } else if( c1 == 'x' ) {
                // find next unmatched y in s2 and swap
                int j = i+1;
                for(;j < n; ++j)
                    if( s2[j] == 'y' && s1[j] == 'x' )
                        break;
                if( j == n ) {
                    if( i == n-1 )
                        break;
                    // swap current only
                    ++ans;
                    s1[i] = 'y';
                    s2[i] = 'x';
                    ++r;
                    continue;
                }
                // swap and advance
                ++ans;
                s2[j] = 'x';
                s1[i] = 'y'; // TODO comment out
                ++i;
                r = 0;

            } else {    // c1 == 'y'
                // find next unmatched x in s2 and swap
                int j = i+1;
                for(;j < n; ++j)
                    if( s2[j] == 'x' && s1[j] == 'y' )
                        break;
                if( j == n ) {
                    if( i == n-1 )
                        break;
                    // swap current only
                    ++ans;
                    s1[i] = 'x';
                    s2[i] = 'y';
                    ++r;
                    continue;
                }
                // swap and advance
                ++ans;
                s2[j] = 'y';
                s1[i] = 'x'; // TODO comment out
                ++i;
                r = 0;

            }
        }

        //cout << "s1 " << s1 << endl;
        //cout << "s2 " << s2 << endl;
        //cout << "ans " << ans << endl;
        //cout << "i " << i << endl;

        return i == n ? ans : -1;

        /*
        if( i == n )
            return ans;
        else // i == n-1
            return -1;
        */
    }
};
