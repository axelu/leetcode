
// 489. Robot Room Cleaner
// https://leetcode.com/problems/robot-room-cleaner/



/**
 * // This is the robot's control interface.
 * // You should not implement it, or speculate about its implementation
 * class Robot {
 *   public:
 *     // Returns true if the cell in front is open and robot moves into the cell.
 *     // Returns false if the cell in front is blocked and robot stays in the current cell.
 *     bool move();
 *
 *     // Robot will stay in the same cell after calling turnLeft/turnRight.
 *     // Each turn will be 90 degrees.
 *     void turnLeft();
 *     void turnRight();
 *
 *     // Clean the current cell.
 *     void clean();
 * };
 */

class Solution {
private:
    unordered_map<int,unordered_set<int>> seen; // row,col

    void markAsClean(int i, int j) {
        auto fr = seen.find(i);
        if( fr == seen.end() )
            seen.insert({i,{j}});
        else
            fr->second.insert(j);
    }

    bool isClean(int i, int j) {
        auto fr = seen.find(i);
        if( fr == seen.end() ) {
            return false;
        } else {
            if( fr->second.find(j) == fr->second.end() ) {
                return false;
            }
        }
        return true;
    }


    void dfs(int i, int j, int dir, Robot& robot) {
        // i and j is the cell we are stepping on
        // dir is the direction our robot faces when we step on this cell
        // 0 North, 1 East, 2 South, 3 West

        // clean the cell we stept on
        robot.clean();
        markAsClean(i,j);

        int i_new, j_new, dir_new;

        // clean the left cell
        if( dir == 0 ) {
            i_new   = i;
            j_new   = j-1;
            dir_new = 3;
        } else if( dir == 1 ) {
            i_new   = i-1;
            j_new   = j;
            dir_new = 0;
        } else if( dir == 2 ) {
            i_new   = i;
            j_new   = j+1;
            dir_new = 1;
        } else {
            // dir == 3
            i_new   = i+1;
            j_new   = j;
            dir_new = 2;
        }
        if( !isClean(i_new,j_new) ) {
            robot.turnLeft();
            if( robot.move() ) {
                dfs(i_new,j_new,dir_new,robot);
                // restore original direction
                robot.turnLeft();
            } else {
                // restore original direction
                robot.turnRight();
            }
        }
        // robot will point in the direction that it came
        // when it originally stepped onto this cell


        // clean the cell straight in front of us
        if( dir == 0 ) {
            i_new   = i-1;
            j_new   = j;
            dir_new = 0;
        } else if( dir == 1 ) {
            i_new   = i;
            j_new   = j+1;
            dir_new = 1;
        } else if( dir == 2 ) {
            i_new   = i+1;
            j_new   = j;
            dir_new = 2;
        } else {
            // dir == 3
            i_new   = i;
            j_new   = j-1;
            dir_new = 3;
        }
        if( !isClean(i_new,j_new) ) {
            if( robot.move() ) {
                dfs(i_new,j_new,dir_new,robot);
                // point in the next direction
                robot.turnLeft();
            } else {
                // point in the next direction
                robot.turnRight();
            }
        } else {
            // point in the next direction
            robot.turnRight();
        }
        // robot will point in the direction of the right cell
        // relative to the direction that it came
        // when it originally stepped onto this cell


        // clean the right cell
        // NOTE: robot already points in this direction!!!
        if( dir == 0 ) {
            i_new   = i;
            j_new   = j+1;
            dir_new = 1;
        } else if( dir == 1 ) {
            i_new   = i+1;
            j_new   = j;
            dir_new = 2;
        } else if( dir == 2 ) {
            i_new   = i;
            j_new   = j-1;
            dir_new = 3;
        } else {
            // dir == 3
            i_new   = i-1;
            j_new   = j;
            dir_new = 0;
        }
        if( !isClean(i_new,j_new) ) {
            if( robot.move() ) {
                dfs(i_new,j_new,dir_new,robot);
                // point in the next direction
                robot.turnLeft();
            } else {
                // point in the next direction
                robot.turnRight();
            }
        } else {
            // point in the next direction
            robot.turnRight();
        }
        // the robot will point oposite the direction that it came
        // when it origionally stepped onto this cell

        // return to the cell we came from
        robot.move();
    }

public:
    void cleanRoom(Robot& robot) {
        // we don't know our starting cell in the grid
        // nor do we know how big the grid is
        // we will set start position to 0,0 and
        // we will assume imin,jmin >= INT_MIN and imax,jmax <= INT_MAX

        // clean the starting cell
        robot.clean();
        markAsClean(0,0);

        // we need to start our robot in all four directions
        int i[4] = {-1,0,1,0};
        int j[4] = {0,1,0,-1};
        for(int dir = 0; dir < 4; ++dir) {
            if( !isClean(i[dir],j[dir] ) ) {
                if( robot.move() ) {
                    dfs(i[dir],j[dir],dir,robot);
                    robot.turnLeft();
                } else {
                    robot.turnRight();
                }
            } else {
                robot.turnRight();
            }
        }

    }
};
