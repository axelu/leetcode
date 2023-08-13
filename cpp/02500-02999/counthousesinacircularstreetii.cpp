
// 2753. Count Houses in a Circular Street II
// https://leetcode.com/problems/count-houses-in-a-circular-street-ii/




/**
 * Definition for a street.
 * class Street {
 * public:
 *     Street(vector<int> doors);
 *     void closeDoor();
 *     bool isDoorOpen();
 *     void moveRight();
 * };
 */
class Solution {
public:
    int houseCount(Street* street, int k) {
        // idea:
        // move till we are in front of an open door (problem description says at least one door is open)
        // then move right and save if we encounter an open door, then close that door
        // do that k times and the last time we encountered an open door is the answer

        for(int i = 0; i < k; ++i) {
            if( street->isDoorOpen() )
                break;
            street->moveRight();
        }
        // we are standing in front of an open door
        int ans = 1;
        street->moveRight();
        for(int i = 1; i <= k; ++i) {
            if( street->isDoorOpen() ) {
                ans = i;
                street->closeDoor();
            }
            street->moveRight();
        }

        return ans;
    }
};
