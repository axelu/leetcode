
// 2069. Walking Robot Simulation II
// https://leetcode.com/problems/walking-robot-simulation-ii/



class Robot {
private:
    int i,s0s,s0e,s1s,s1e,s2s,s2e,s3s,s3e,n,w,h;
    bool hasMoved;

public:
    Robot(int width, int height) {
        n = 2*(width-1) + 2*(height-1);
        w = width, h = height;
        // sectors
        s0s = 1,        s0e = width-1;
        s1s = s0e + 1,  s1e = s0e + (height-1);
        s2s = s1e + 1,  s2e = s1e + (width-1);
        s3s = s2e + 1,  s3e = s2e + (height-1);
        i = 0;
        hasMoved = false;
        // our robot runs around the edge of the grid
        // we define four sectors: 0,2,3,4
        // it is determined in each sector which direction
        // the robot points
    }

    void step(int num) {
        i += num%n;
        if( i >= n )
            i = i % n;
        hasMoved = true;
    }

    vector<int> getPos() {
        int x,y;
        if( i <= s0e ) {
            x = i;
            y = 0;
        } else if( i <= s1e ) {
            x = w-1;
            y = 1 + (i - s1s);
        } else if( i <= s2e ) {
            x = (w-2)-(i-s2s);;
            y = h-1;
        } else {
            x = 0;
            y = (h-2)-(i-s3s);
        }
        return {x,y};
    }

    string getDir() {
        if( i == 0 ) {
            return hasMoved ? "South" : "East";
        } else if( i <= s0e ) {
            return "East";
        } else if( i <= s1e ) {
            return "North";
        } else if( i <= s2e ) {
            return "West";
        } else {
            return "South";
        }
    }
};

/**
 * Your Robot object will be instantiated and called as such:
 * Robot* obj = new Robot(width, height);
 * obj->step(num);
 * vector<int> param_2 = obj->getPos();
 * string param_3 = obj->getDir();
 */
