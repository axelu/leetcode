
// 2211. Count Collisions on a Road
// https://leetcode.com/problems/count-collisions-on-a-road/




class Solution {
public:
    int countCollisions(string directions) {
        int n = directions.size();
        if( n == 0 )
            return 0;

        int ans = 0;

        // pass 1
        // we will move from left to right aka going right
        // through directions
        // we will keep track of either the last car encountered
        // being either stationary or going right
        // then when we come to a car going left, we either know
        // if it accounts for 1 (colliding with a stationary car)
        // or 2 points (colliding with a right moving car)
        // note that the left moving car now becomes a stationary car
        char last = '#';
        for(int i = 0; i < n; ++i) {

            if( directions[i] == 'R' ) {
                last = 'R';

            } else if( directions[i] == 'S' ) {
                last = 'S';

            } else { // directions[i] == 'L'
                if( last == 'S' ) {
                    ans += 1;
                    last = 'S';
                } else if( last == 'R' ) {
                    ans += 2;
                    last = 'S';
                }
            }
        }

        cout << ans << endl;

        // pass 2
        // opposite as pass 1
        last = '#';
        for(int i = n-1; i >= 0; --i) {

            if( directions[i] == 'L' ) {
                last = 'L';

            } else if( directions[i] == 'S' ) {
                last = 'S';

            } else { // directions[i] == 'R'
                if( last == 'S' ) {
                    ans += 1;
                    last = 'S';
                } else if( last == 'L' ) {
                    // don't double count
                    // ans += 2;
                    last = 'S';
                }
            }
        }

        return ans;
    }
};
