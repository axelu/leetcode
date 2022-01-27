
// 531. Lonely Pixel I
// https://leetcode.com/problems/lonely-pixel-i/





class Solution {
public:
    int findLonelyPixel(vector<vector<char>>& picture) {
        int m = picture.size();
        int n = picture[0].size();

        int rowCnt[m];memset(rowCnt,0,sizeof rowCnt);
        int colCnt[n];memset(colCnt,0,sizeof colCnt);

        int i,j;

        int ans = 0;

        // pass 1
        for(i = 0; i < m; ++i)
            for(j = 0; j < n; ++j)
                if( picture[i][j] == 'B' ) {
                    ++rowCnt[i];
                    ++colCnt[j];
                }


        // pass 2
        for(i = 0; i < m; ++i)
            for(j = 0; j < n; ++j)
                if( picture[i][j] == 'B' && rowCnt[i] == 1 && colCnt[j] == 1 )
                    ++ans;


        return ans;

    }
};
