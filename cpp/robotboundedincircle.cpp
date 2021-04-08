
// day 17 September 2020 challenge
// Robot Bounded in Circle
// https://leetcode.com/problems/robot-bounded-in-circle/


#include <iostream>
#include <cassert>

#include <string>

using namespace std;

class Solution {
public:
    bool isRobotBounded(string instructions) {
        enum directions {NORTH, EAST, SOUTH, WEST};

        int dir = NORTH;    // initial direction
        int x = 0;          // initial x coordinate
        int y = 0;          // initial y coordinate

        for(char c : instructions) {
            switch(c) {
                case 'G' :  if( dir == NORTH) {
                                ++x;
                            } else if ( dir == SOUTH ) {
                                --x;
                            } else if ( dir == EAST ) {
                                ++y;
                            } else {
                                // WEST
                                --y;
                            }
                            break;
                case 'L' :  if( dir == NORTH ) {
                                dir = WEST;
                            } else {
                                --dir;
                            }
                            break;
                case 'R' :  if( dir == WEST ) {
                                dir = NORTH;
                            } else {
                                ++dir;
                            }
                            break;
            }
        }

        if( x == 0 && y == 0 ) {
            return true;
        } else {
            return ( dir == NORTH ) ? false : true;
        }
    }
};

int main() {

    Solution s;
    string instructions;

    instructions = "GGLLGG";
    assert(s.isRobotBounded(instructions) == true);

    instructions = "GGLLGGGGLLGG";
    assert(s.isRobotBounded(instructions) == true);

    instructions = "GG";
    assert(s.isRobotBounded(instructions) == false);

    instructions = "GLGR";
    assert(s.isRobotBounded(instructions) == false);

    instructions = "GLGRG";
    assert(s.isRobotBounded(instructions) == false);

    instructions = "GL";
    assert(s.isRobotBounded(instructions) == true);

    instructions = "GLL";
    assert(s.isRobotBounded(instructions) == true);

    instructions = "GLLL";
    assert(s.isRobotBounded(instructions) == true);

    instructions = "GLLLL";
    assert(s.isRobotBounded(instructions) == false);

    instructions = "LG";
    assert(s.isRobotBounded(instructions) == true);

    instructions = "RGL";
    assert(s.isRobotBounded(instructions) == false);

    instructions = "RGR";
    assert(s.isRobotBounded(instructions) == true);

    instructions = "LGR";
    assert(s.isRobotBounded(instructions) == false);

    instructions = "LLL";
    assert(s.isRobotBounded(instructions) == true);

    instructions = "LLLL";
    assert(s.isRobotBounded(instructions) == true);

    return 0;
}

