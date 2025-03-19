
// 3443. Maximum Manhattan Distance After K Changes
// https://leetcode.com/problems/maximum-manhattan-distance-after-k-changes/





class Solution {
public:
    int maxDistance(string s, int k) {
        int n = s.size();

        // Manhattan Distance between two cells (xi, yi) and (xj, yj) is:
        //     |xi - xj| + |yi - yj|
        // we are starting at (0, 0)
        // let E be x+1 and W be x-1
        // let N be y+1 and S be y-1

        int mx = 0;
        int mn = 0;
        int pcarry = 0; int pk = k;
        int ncarry = 0; int nk = k;
        int manhattan = 0; // initial Manhattan Distance
        int x = 0; int y = 0;
        for(int i = 0; i < n; ++i) {
            if( s[i] == 'E' )
                ++x;
            else if( s[i] == 'W' )
                --x;
            else if( s[i] == 'N' )
                ++y;
            else // s[i] == 'S'
                --y;

            int manhattan_new = abs(x) + abs(y);
            if( manhattan_new > manhattan ) {
                // lets reverse all positive
                if( pk > 0 ) {
                    pcarry += 2;
                    --pk;
                }

            } else {
                // lets reverse all negative
                if( nk > 0 ) {
                    ncarry += 2;
                    --nk;
                }
            }

            mx = max(mx, manhattan_new);
            mn = min(mn, manhattan_new);

            mn = min(mn, manhattan_new - pcarry);
            mx = max(mx, manhattan_new + ncarry);

            manhattan = manhattan_new;
        }


        return max(abs(mn), mx);
    }
};
