
// 3694. Distinct Points Reachable After Substring Removal
// https://leetcode.com/problems/distinct-points-reachable-after-substring-removal/



class Solution {
public:
    int distinctPoints(string s, int k) {
        int n = s.size();

        if( k == n )
            return 1;

        int ans = 1;

        // start by assuming that prefix of length k
        // has been removed, so execute k..n-1

        int x = 0, y = 0;
        for(int i = k; i < n; ++i) {
            if( s[i] == 'U' )
                ++y;
            else if( s[i] == 'D' )
                --y;
            else if( s[i] == 'L' )
                --x;
            else // s[i] == 'R'
                ++x;
        }

        // cout << "initial x " << x << " y " << y << endl;

        set<pair<int,int>> st;
        st.insert({x,y});

        for(int i = 0, j = k; j < n; ++j, ++i) {
            // reverse step j aka move opposite
            if( s[j] == 'U' )
                --y;
            else if( s[j] == 'D' )
                ++y;
            else if( s[j] == 'L' )
                ++x;
            else // s[j] == 'R'
                --x;

            // apply step i
            if( s[i] == 'U' )
                ++y;
            else if( s[i] == 'D' )
                --y;
            else if( s[i] == 'L' )
                --x;
            else // s[i] == 'R'
                ++x;

            // cout << "j " << j << " x " << x << " y " << y << endl;

            if( st.insert({x,y}).second )
                ++ans;
        }

        return ans;
    }
};
