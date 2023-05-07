
// 1861. Rotating the Box
// https://leetcode.com/problems/rotating-the-box/




class Solution {
private:
    vector<vector<char>> rotate90(vector<vector<char>>& A) {
        int m = A.size();
        int n = A[0].size();

        vector<vector<char>> B(n,vector<char>(m,0));
        for(int i = 0; i < m; ++i)
            for(int j = 0; j < n; ++j)
                B[j][m-1-i] = A[i][j];

        return B;
    }

public:
    vector<vector<char>> rotateTheBox(vector<vector<char>>& box) {
        box = rotate90(box);

        int m = box.size();     // rows after rotation
        int n = box[0].size();  // cols after rotation

        // walk columns from bottom up
        for(int j = 0; j < n; ++j) {

            // stone rests on obstacle, another stone or bottom of box
            // we need to keep track of row that a rock could fall to
            int rest_row = m-1;
            for(int i = m-1; i >= 0; --i) {

                if( box[i][j] == '*' ) {        // obstacle
                    rest_row = i-1;
                } else if( box[i][j] == '#' ) { // stone
                    // will the stone fall through?
                    if( rest_row > i ) {
                        // stone falls to rest_row
                        box[rest_row][j] = '#';
                        box[i][j] = '.';
                    }
                    --rest_row;
                }
            }
        }


        return box;
    }
};
