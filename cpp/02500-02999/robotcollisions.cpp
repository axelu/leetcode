
// 2751. Robot Collisions
// https://leetcode.com/problems/robot-collisions/

class Solution {
private:
    struct Robot {
        int id;
        int position; // initial position
        int health;
        char direction;
        Robot(int id, int position, int health, char direction) : id(id), position(position), health(health), direction(direction) {}
    };
    
public:
    vector<int> survivedRobotsHealths(vector<int>& positions, vector<int>& healths, string directions) {
        int n = positions.size(); // positions.length == healths.length == directions.length
        if( n == 1 )
            return {healths[0]};
        
        // we are done if either
        //    only one robot left OR
        //    all remaining robots are moving in the same direction OR
        //    all robots at positions <= x move left and all robots at positions > x move right
        
        // two robots will collide if 
        //     the robot at the lower position moves R AND
        //     the robot at the greater position moves L
        
        vector<Robot*> v(n);
        for(int i = 0; i < n; ++i)
            v[i] = new Robot(i,positions[i],healths[i],directions[i]);
        // sort robots by position
        sort(begin(v),end(v),[](Robot* a, Robot* b){
           return a->position < b->position; // values in positions are distinct
        });
        /*
        // debug
        for(Robot* rb: v)
            cout << rb->id << ":" << rb->position << ":" << rb->health << ":" << rb->direction << " ";
        cout << endl;
        */
        
        // let us go left to right
        deque<Robot*> stck; // top is left robot
        for(int i = 0; i < n; ) {
            if( stck.empty() ) {
                stck.push_back(v[i]);
                ++i;
                continue;
            }
            
            Robot* left_robot = stck.back();
            Robot* right_robot = v[i];
            
            if( left_robot->direction == 'R' && right_robot->direction == 'L' ) {
                // left_robot and right_robot will collide
                
                if( left_robot->health > right_robot->health ) {
                    // left_robot survives
                    --left_robot->health;
                    ++i;

                } else if( left_robot->health < right_robot->health ) { 
                    // right_robot survives
                    stck.pop_back();
                    --right_robot->health;
                    // because the right_robot is moving left, it may collide
                    // with the robot (if any) to its left

                } else { // left_robot->health == right_robot->health
                    // neither robot survives
                    stck.pop_back();
                    ++i;                     
                }
             
            } else {
                stck.push_back(right_robot);
                ++i;
            }
        }
        
        int ans_sz = stck.size();
        if( ans_sz == 0 )
            return {};
        
        // sort robots by id
        sort(begin(stck),end(stck),[](Robot* a, Robot* b){
           return a->id < b->id; // id's are distinct
        });
        
        
        vector<int> ans(ans_sz);
        int i = 0;
        while( !stck.empty() ) {
            ans[i] = stck.front()->health;
            stck.pop_front();
            ++i;
        }
        
        return ans;
    }
};


// passes 2429/2433 test cases, then TLE as of 10/12/2023

class Solution {
private:
    struct Robot {
        int id;
        int position; // initial position
        int health;
        char direction;
        Robot(int id, int position, int health, char direction) : id(id), position(position), health(health), direction(direction) {}
    };

public:
    vector<int> survivedRobotsHealths(vector<int>& positions, vector<int>& healths, string directions) {
        int n = positions.size(); // positions.length == healths.length == directions.length
        if( n == 1 )
            return {healths[0]};

        // we are done if either
        //    only one robot left OR
        //    all remaining robots are moving in the same direction OR
        //    all robots at positions <= x move left and all robots at positions > x move right

        // two robots will collide if
        //     the robot at the lower position moves R AND
        //     the robot at the greater position moves L

        deque<Robot*> dq;
        for(int i = 0; i < n; ++i)
            dq.push_front(new Robot(i,positions[i],healths[i],directions[i]));
        // sort robots by position
        sort(begin(dq),end(dq),[](Robot* a, Robot* b){
           return a->position < b->position; // values in positions are distinct
        });
        /*
        // debug
        for(Robot* rb: dq)
            cout << rb->id << ":" << rb->position << ":" << rb->health << ":" << rb->direction << " ";
        cout << endl;
        */

        while( true ) {

            int collision_cnt = 0;
            deque<Robot*> dq_new;

            Robot* right_robot = dq.back();
            dq.pop_back();

            while( !dq.empty() ) {
                Robot* left_robot = dq.back();
                dq.pop_back();

                if( left_robot->direction == 'R' && right_robot->direction == 'L' ) {
                    // left_robot and right_robot will collide
                    ++collision_cnt;

                    if( left_robot->health > right_robot->health ) {
                        // left_robot survives
                        --left_robot->health;
                        // because the left_robot is moving right, it will NOT collide
                        // with the robot (if any) to its left
                        dq_new.push_front(left_robot);
                        if( !dq.empty() ) {
                            right_robot = dq.back();
                            dq.pop_back();
                        } else {
                            right_robot = nullptr;
                        }

                    } else if( left_robot->health < right_robot->health ) {
                        // right_robot survives
                        --right_robot->health;
                        // because the right_robot is moving left, it will may collide
                        // with the robot (if any) to its left

                    } else { // left_robot->health == right_robot->health
                        // neither robot survives
                        if( !dq.empty() ) {
                            right_robot = dq.back();
                            dq.pop_back();
                        } else {
                            right_robot = nullptr;
                        }
                    }

                } else {
                    // left_robot and right_robot will NOT collide
                    // either both are moving in the same direction OR
                    // they are moving away from each other
                    dq_new.push_front(right_robot);
                    right_robot = left_robot;
                }
            }

            if( right_robot != nullptr )
                dq_new.push_front(right_robot);

            dq = dq_new;
            if( dq.size() <= 1 || collision_cnt == 0 )
                break;
        }

        int ans_sz = dq.size();
        if( ans_sz == 0 )
            return {};

        // sort robots by id
        sort(begin(dq),end(dq),[](Robot* a, Robot* b){
           return a->id < b->id; // id's are distinct
        });


        vector<int> ans(ans_sz);
        int i = 0;
        while( !dq.empty() ) {
            ans[i] = dq.front()->health;
            dq.pop_front();
            ++i;
        }

        return ans;
    }
};
