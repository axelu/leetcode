
// 2463. Minimum Total Distance Traveled
// https://leetcode.com/problems/minimum-total-distance-traveled/




class Solution {
private:
    int robot_sz,factory_sz;
    int * _robot;
    vector<int> * _factory;
    long long mem[100][100];

    long long rec(int i, int j) {
        // i robot idx, j factory idx
        // cout << "rec i " << i << " j " << j << endl;

        if( i == robot_sz )     // all robots are repaired
            return 0;
        if( j == factory_sz )   // no more factories left
            return 200000000001;

        if( mem[i][j] != -1 )
            return mem[i][j];

        // we have a choice
        //    repair k robots in factory j with 0 <= k <= _factory[j][1]

        long long ret = rec(i,j+1);
        long long t = 0;
        for(int k = 0; k < _factory[j][1] && i+k < robot_sz; ++k) {

            t = t + abs(_factory[j][0] - _robot[i+k]);
            ret = min(ret, t + rec(i+k+1,j+1));
        }

        return mem[i][j] = ret;
    }


public:
    long long minimumTotalDistance(vector<int>& robot, vector<vector<int>>& factory) {
        robot_sz = robot.size();
        factory_sz = factory.size();

        sort(robot.begin(),robot.end());
        sort(factory.begin(),factory.end());

        // debug
        /*
        cout << "robots ";
        for(auto& i: robot)
            cout << i << " ";
        cout << endl;
        cout << "factories ";
        for(auto& v: factory)
            cout << v[0] << ":" << v[1] << " ";
        cout << endl;
        */

        _robot = robot.data();
        _factory = factory.data();

        memset(mem,-1,sizeof mem);
        return rec(0,0);
    }
};
