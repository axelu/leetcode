
// 1753. Maximum Score From Removing Stones
// https://leetcode.com/problems/maximum-score-from-removing-stones/






class Solution {
public:
    int maximumScore(int a, int b, int c) {
        // hint 1 states:
        // "It's optimal to always remove one stone from the biggest 2 piles"
        // Related Topic states : Greedy

        // 1 <= a, b, c <= 10^5
        /*
        if( (a == 0 && b == 0) ||
            (a == 0 && c == 0) ||
            (b == 0 && c == 0) )
            return 0;
        */


        vector<int> v = {a,b,c};
        // cout << "0 " << v[0] << " " << v[1] << " " << v[2] << endl;

        auto s = begin(v), e = prev(end(v)), ee = end(v);
        int ans = 0;
        pair<vector<int>::iterator,vector<int>::iterator> p;
        while( true) {
            ++ans;
            p = minmax_element(s,ee);

            if( *p.first == 0 ) {
                // cout << "min is 0 " << endl;
                if( p.first == s ) {
                    // cout << "min is a" << endl;
                    if( p.second == e )
                        --v[1];
                    else
                        --v[2];
                } else if(p.first == e ) {
                    // cout << "min is c" << endl;
                    if( p.second == s )
                        --v[1];
                    else
                        --v[0];
                } else {
                    // cout << "min is b" << endl;
                    if( p.second == e )
                        --v[0];
                    else
                        --v[2];
                }
            } else
                --(*p.first);

            --(*p.second);

            // cout << ans << " " << v[0] << " " << v[1] << " " << v[2] << endl;

            if( (v[0] == 0 && v[1] == 0) ||
                (v[0] == 0 && v[2] == 0) ||
                (v[1] == 0 && v[2] == 0) )
                break;
        }

        return ans;
    }
};
