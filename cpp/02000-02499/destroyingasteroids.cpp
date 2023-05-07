
// 2126. Destroying Asteroids
// https://leetcode.com/problems/destroying-asteroids/




class Solution {
public:
    bool asteroidsDestroyed(int mass, vector<int>& asteroids) {
        // we need to gain as much mass as we can without getting destroyed
        // said differently
        // it is best to collide with astroid who's mass it the largest smaller then planet's mass

        sort(asteroids.begin(),asteroids.end());

        long m = mass;
        for(long x: asteroids) {
            if( x > m )
                return false;
            m += x;
        }

        return true;
    }
};
