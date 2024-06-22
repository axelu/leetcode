
// 3025. Find the Number of Ways to Place People I
// https://leetcode.com/problems/find-the-number-of-ways-to-place-people-i/




class Solution {
public:
    int numberOfPairs(vector<vector<int>>& points) {
        int n = points.size(); // 2 <= n <= 50, points[i] = [xi, yi]

        sort(points.begin(),points.end(),[](const vector<int>& a, const vector<int>& b){
            if( a[0] < b[0] ) {
                return true;
            } else if( a[0] == b[0] ) {
                if( a[1] > b[1] ) {
                    return true;
                }
            }
            return false;
        });
        // debug
        /*
        for(vector<int>& p: points) {
            cout << p[0] << "," << p[1] << " ";
        }
        cout << endl;
        */

        int ans = 0;

        for(int i = 0; i < n-1; ++i) {
            // Chisato at upper left corner x1, y1
            int x1 = points[i][0];
            int y1 = points[i][1];

            // all points i-1 (if any) will be outside the fence because of our sorting
            for(int j = i+1; j < n; ++j) {
                // Takina at lower right corner x2, y2
                int x2 = points[j][0];
                int y2 = points[j][1];
                if( y2 > y1 ) // has to be the LOWER right corner
                    continue;

                if( y1 == y2 ) {
                    // horizontal line
                    bool is_chisato_sad = false;
                    for(int k = i+1; k < n; ++k) {
                        if( k == j )
                            break;
                        int x = points[k][0];
                        int y = points[k][1];
                        if( y != y1 )
                            continue;
                        is_chisato_sad = true;
                        break;
                    }
                    if( !is_chisato_sad )
                        ++ans;

                } else if( x1 == x2 ) {
                    // vertical line
                    bool is_chisato_sad = false;
                    for(int k = i+1; k < n; ++k) {
                        if( k == j )
                            break;
                        int x = points[k][0];
                        int y = points[k][1];
                        if( x == x1 ) {
                            is_chisato_sad = true;
                            break;
                        }
                    }
                    if( !is_chisato_sad )
                        ++ans;

                } else {
                    // rectangle
                    bool is_chisato_sad = false;
                    for(int k = i+1; k < n; ++k) {
                        if( k == j )
                            break;
                        int x = points[k][0];
                        int y = points[k][1];
                        if( x >= x1 && x <= x2 && y <= y1 && y >= y2 ) {
                            is_chisato_sad = true;
                            break;
                        }
                    }
                    if( !is_chisato_sad )
                        ++ans;

                }
            }
        }

        return ans;
    }
};
