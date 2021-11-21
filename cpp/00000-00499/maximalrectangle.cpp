
// 85. Maximal Rectangle
// https://leetcode.com/problems/maximal-rectangle/



class Solution {
private:
    // https://leetcode.com/problems/largest-rectangle-in-histogram/
    int largestRectangleArea(int n, int heights[]) {
        if( n == 1 ) return heights[0];

        int ans = 0, idx;
        priority_queue<array<int,2>> q;
        array<int,2> qe;
        for(int i = 0; i < n; ++i) {
            if( q.empty() ) {
                q.push({heights[i],i});
                continue;
            }
            idx = -1;
            while( !q.empty() ) {
                qe = q.top();
                if( qe[0] == heights[i] ) {
                    idx = -1;
                    break;
                } else if( qe[0] < heights[i] ) {
                    if( idx == -1 ) idx = i;
                    break;
                } else {
                    // qe[0] > heights[i]
                    idx = qe[1];
                    ans = max(ans,qe[0]*(i-qe[1]));
                    q.pop();
                }
            }
            if( idx != -1 )
                q.push({heights[i],idx});
        }
        // finish up
        while( !q.empty() ) {
            qe = q.top();
            q.pop();
            ans = max(ans,qe[0]*(n-qe[1]));
        }

        return ans;
    }

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

            for(int j = 0; j < n; ++j) {    // col
                if( matrix[i][j] == '0' )
                    curHeights[j] = 0;
                else
                    curHeights[j] = 1 + preHeights[j];
            }
            ans = max(ans,largestRectangleArea(n,curHeights));
        }

        return ans;
    }
};
