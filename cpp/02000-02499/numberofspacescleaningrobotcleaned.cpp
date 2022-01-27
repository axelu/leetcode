
// 2061. Number of Spaces Cleaning Robot Cleaned
// https://leetcode.com/problems/number-of-spaces-cleaning-robot-cleaned/




class Solution {
public:
    int numberOfCleanRooms(vector<vector<int>>& room) {
        // a given space is only cleaned once
        // if we enter space a second time from the same direction,
        // then we are done (cycle)

        int m = room.size();     // rows
        int n = room[0].size();  // cols
        int seen[m][n];memset(seen,0,sizeof seen);
                                 // seen = mask of direction entered
                                 // bit 0 from left (bit 0 is rightmost bit)
                                 // bit 1 from top, bit 2 from right, bit 3 from bottom

        int ans = 1;        // top left corner of room will be empty in all cases

        seen[0][0] = 1;     // mark starting cell as clean, entered from left = from outside room

        int direction = 0;  // 0 moving right, 1 moving down, 2 moving left, 3 moving up
        int dirR[4] = {0,1,0,-1};
        int dirC[4] = {1,0,-1,0};

        // run the robot
        int i = 0,j = 0;    // initial position row 0 (i) and col 0 (j)
        int i_new,j_new;
        while(true) {

            bool moved = false;
            for(int k = 0; k < 4; ++k) {
                i_new = i + dirR[direction];
                if( i_new < 0 || i_new == m ) {
                    ++direction;
                    if( direction == 4 )
                        direction = 0;
                    continue;
                }

                j_new = j + dirC[direction];
                if( j_new < 0 || j_new == n ) {
                    ++direction;
                    if( direction == 4 )
                        direction = 0;
                    continue;
                }

                if( room[i_new][j_new] == 1 ) {
                    ++direction;
                    if( direction == 4 )
                        direction = 0;
                    continue;
                }

                moved = true;
            }
            if( !moved )
                break;

            if( !seen[i_new][j_new] )
                ++ans;

            if( (seen[i_new][j_new]  >> direction) & 1 )
                break;

            seen[i_new][j_new] |= 1 << direction;
            i = i_new;
            j = j_new;
        }

        return ans;
    }
};
