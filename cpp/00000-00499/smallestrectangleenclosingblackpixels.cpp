
// 302. Smallest Rectangle Enclosing Black Pixels
// https://leetcode.com/problems/smallest-rectangle-enclosing-black-pixels/



class Solution {
private:
    int m,n,xmn,ymn,xmx,ymx;

    // directions
    int dirR[4] = {0,1,0,-1};
    int dirC[4] = {1,0,-1,0};

    void explore(vector<vector<char>>& image, int x, int y, int seen[]) {
        int seenIdx = x*n+y;
        seen[seenIdx] = 1;

        xmn = min(xmn,x);
        ymn = min(ymn,y);
        xmx = max(xmx,x);
        ymx = max(ymx,y);

        // explore all 4 directions
        int x_new,y_new;
        for(int k = 0; k < 4; ++k) {
            x_new = x + dirR[k];
            if( x_new < 0 || x_new == m )
                continue;

            y_new = y + dirC[k];
            if( y_new < 0 || y_new == n )
                continue;

            if( image[x_new][y_new] == '0' )
                continue;

            if( seen[x_new*n+y_new] )
                continue;

            explore(image,x_new,y_new,seen);
        }
    }

public:
    int minArea(vector<vector<char>>& image, int x, int y) {
        m = image.size();
        n = image[0].size();
        xmn = x, ymn = y, xmx = x, ymx = y;

        int seen[m*n];memset(seen,0,sizeof seen);

        explore(image,x,y,seen);



        return (xmx-xmn+1)*(ymx-ymn+1);
    }
};
