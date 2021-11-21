
// 85. Maximal Rectangle
// https://leetcode.com/problems/maximal-rectangle/



// see also https://leetcode.com/problems/largest-rectangle-in-histogram/

class Solution {
public:
    int maximalRectangle(vector<vector<char>>& matrix) {
        int m = matrix.size();      // rows
        if( m == 0 )
            return 0;
        int n = matrix[0].size();   // cols
        if( n == 0 )
            return 0;

        int ans = 0;

        int _oddHeights[n];memset(_oddHeights,0,sizeof _oddHeights);
        int _evenHeights[n];
        int * curHeights;
        int * preHeights;
        for(int i = 0; i < m; ++i) {        // row
            if( i%2 == 0 ) {
                curHeights = _evenHeights;
                preHeights = _oddHeights;
            } else {
                curHeights = _oddHeights;;
                preHeights = _evenHeights;
            }


            int t = 0, idx;
            priority_queue<array<int,2>> q;
            array<int,2> qe;

            for(int j = 0; j < n; ++j) {    // col
                if( matrix[i][j] == '0' )
                    curHeights[j] = 0;
                else
                    curHeights[j] = 1 + preHeights[j];


                if( q.empty() ) {
                    q.push({curHeights[j],j});
                    continue;
                }
                idx = -1;
                while( !q.empty() ) {
                    qe = q.top();
                    if( qe[0] == curHeights[j] ) {
                        idx = -1;
                        break;
                    } else if( qe[0] < curHeights[j] ) {
                        if( idx == -1 ) idx = j;
                        break;
                    } else {
                        // qe[0] > curHeights[j]
                        idx = qe[1];
                        t = max(t,qe[0]*(j-qe[1]));
                        q.pop();
                    }
                }
                if( idx != -1 )
                    q.push({curHeights[j],idx});

            }
            // finish up
            while( !q.empty() ) {
                qe = q.top();
                q.pop();
                t = max(t,qe[0]*(n-qe[1]));
            }
            ans = max(ans,t);
        }

        return ans;
    }
};
