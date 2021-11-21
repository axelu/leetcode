
// 135. Candy
// https://leetcode.com/problems/candy/
// day 27 June 2021 challenge
// https://leetcode.com/explore/featured/card/june-leetcoding-challenge-2021/606/week-4-june-22nd-june-28th/3793/




class Solution {
public:
    int candy(vector<int>& ratings) {
        int n = ratings.size();
        if( n == 1 ) return 1;

        vector<int> v(n,1); // each child must have at least one candy

        stack<int> stck;
        int d,idx;
        for(int i = 0; i < n-1; ++i) {
            // peek ahead
            if( ratings[i+1] >= ratings[i] ) {
                // if we came here from an incline, there is nothing to do
                // if we came here from a decline, we need to go back
                // and adjust the elements up to the last peak
                d = 2;
                while( !stck.empty() ) {
                    idx = stck.top();
                    stck.pop();
                    if( d > v[idx] )
                        v[idx] = d;
                    ++d;
                }
            }
            if( ratings[i+1] > ratings[i] ) {
                v[i+1] = v[i]+1;
            } else if( ratings[i+1] < ratings[i] ) {
                stck.push(i);
            }
        }

        // finish up
        d = 2;
        while( !stck.empty() ) {
            idx = stck.top();
            stck.pop();
            if( d > v[idx] )
                v[idx] = d;
            ++d;
        }

        /*
        for(int x : v)
            cout << x << " ";
        cout << endl;
        */

        return accumulate(begin(v),end(v),0);
    }
};
