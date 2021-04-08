
// Asteroid Collision
// day 21 October 2020 challenge
// https://leetcode.com/explore/challenge/card/october-leetcoding-challenge/561/week-3-october-15th-october-21st/3502/
// https://leetcode.com/problems/asteroid-collision/



class Solution {
public:
    vector<int> asteroidCollision(vector<int>& asteroids) {
        vector<int> r = {};

        for(auto it = begin(asteroids); it != end(asteroids); ++it) {
            if( r.empty() ) {
                r.push_back(*it);
                continue;
            }
            if( r.back() > 0 && *it < 0 ) {
                // + -
                if( abs(r.back()) == abs(*it) ) {
                    r.pop_back();
                } else if( abs(r.back()) < abs(*it) ) {
                    r.pop_back();
                    --it;
                }
            } else {
                // + +
                // - +
                // - -
                r.push_back(*it);
            }
        }

        return r;
    }
};
