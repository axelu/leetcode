
// 1776. Car Fleet II
// https://leetcode.com/problems/car-fleet-ii/




class Solution {
private:
    double timeToCollision(double c1pos, double c1speed, double c2pos, double c2speed) {
        // calculates the time it takes for car1 to catch up, aka 'collide' with car 2
        // assume: car1 position < car2 position
        //         car1 speed > car2 speed

        return (c2pos-c1pos)/(c1speed-c2speed);
    }
public:
    vector<double> getCollisionTimes(vector<vector<int>>& cars) {
        int n = cars.size();
        vector<double> ans(n,-1);

        stack<int> stck;   // car index
        stck.push(n-1);    // push right most car onto stack
        double t,t1;       // time to collision
        int    rc;         // right car index

        int curCarPos,curCarSpeed;
        for(int i = n-2; i >= 0; --i) {
            curCarPos   = cars[i][0];
            curCarSpeed = cars[i][1];

            // cout << "i " << i << " pos " << curCarPos << " speed " << curCarSpeed << endl;

            while(!stck.empty() && curCarSpeed <= cars[stck.top()][1]) {
                // current car speed slower/equal than its immediate right neighbor,
                // so it will never catch up to it, hence removing the immediate right car
                stck.pop();
            }

            if( !stck.empty() ) {
                rc = stck.top();
                stck.pop();
                // calculate the time it takes for the current car to catch its immediate right neighbor
                t = timeToCollision(curCarPos,curCarSpeed,cars[rc][0],cars[rc][1]);
                while( !stck.empty() ) {
                    // calculate the time it takes for the current car to catch its second to right neighbor
                    t1 = timeToCollision(curCarPos,curCarSpeed,cars[stck.top()][0],cars[stck.top()][1]);

                    // if it takes the current car longer to reach its immediate right neighbor than what
                    // it takes for the current car to reach its second to right neighbor, then the car
                    // to our immidiate right must have caught up to its right car already! hence we can
                    // remove it.
                    if( t > t1 ) {
                        t = t1;
                        rc = stck.top();
                        stck.pop();
                    } else {
                        break;
                    }
                }
                stck.push(rc);
                ans[i] = t;
            }
            stck.push(i);
        }

        return ans;
    }
};
