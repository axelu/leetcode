
// 874. Walking Robot Simulation
// https://leetcode.com/problems/walking-robot-simulation/




class Solution {
public:
    int robotSim(vector<int>& commands, vector<vector<int>>& obstacles) {
        unordered_map<int,unordered_set<int>> usX; // key'd by x
        unordered_map<int,unordered_set<int>> usY; // key'd by y

        int i;
        // pre-processing obstacles
        pair<unordered_map<int,unordered_set<int>>::iterator,bool> p;
        for(i = 0; i < obstacles.size(); ++i) {
            // by X
            p = usX.insert({obstacles[i][0],{obstacles[i][1]}});
            if( !p.second )
                p.first->second.insert(obstacles[i][1]);
            // by Y
            p = usY.insert({obstacles[i][1],{obstacles[i][0]}});
            if( !p.second )
                p.first->second.insert(obstacles[i][0]);
        }

        int x = 0, y = 0; // initial position, x col and y row
        int ans = 0;
        int dir = 0;      // 0 north, 1 east, 2, south, 3 west
        unordered_map<int,unordered_set<int>>::iterator f;
        bool doCalc;
        for(i = 0; i < commands.size(); ++i) {
            if( commands[i] < 0 ) {
                // directional change only, turning in place
                if( commands[i] == -1 ) {
                    // turn right 90 degrees
                    dir = dir == 3 ? 0 : dir + 1;
                } else {
                    // turn left 90 degrees
                    dir = dir == 0 ? 3 : dir -1;
                }
            } else {
                // we are moving
                if( dir == 1 || dir == 3 ) {
                    // we are moving along X (horizontally)
                    // are there obstacles in this 'row'
                    f = usY.find(y);
                    if( f != usY.end() ) {
                        // move to new location step by step checking for obstacle
                        for(int j = 1; j <= commands[i]; ++j) {
                            int x_new = dir == 1 ? x+1 : x-1;
                            if( f->second.find(x_new) != f->second.end() ) {
                                // cell is blocked
                                break;
                            } else {
                                x = x_new;
                            }
                        }
                    } else {
                        // move to new location, no obstacles are in our way
                        x = dir == 1 ? x + commands[i] : x - commands[i];
                    }
                } else {
                    // we are moving along a col (vertically)
                    // are there obstacles in this 'col'
                    f = usX.find(x);
                    if( f != usX.end() ) {
                        // move to new location step by step checking for obstacle
                        for(int j = 1; j <= commands[i]; ++j) {
                            int y_new = dir == 0 ? y+1 : y-1;
                            if( f->second.find(y_new) != f->second.end() ) {
                                // cell is blocked
                                break;
                            } else {
                                y = y_new;
                            }
                        }
                    } else {
                        // move to new location, no obstacles are in our way
                        y = dir == 0 ? y + commands[i] : y - commands[i];
                    }
                }
                // cout << x << " " << y << endl;
                // do the calc
                ans = max(ans,x*x+y*y);
            }
        }
        return ans;
    }
};
