
// 2728. Count Houses in a Circular Street
// https://leetcode.com/problems/count-houses-in-a-circular-street/



/**
 * Definition for a street.
 * class Street {
 * public:
 *     Street(vector<int> doors);
 *     void openDoor();
 *     void closeDoor();
 *     bool isDoorOpen();
 *     void moveRight();
 *     void moveLeft();
 * };
 */
class Solution {
public:
    int houseCount(Street* street, int k) {

        for(int i = 0; i < k; ++i) {
            street->closeDoor();
            street->moveRight();
        }
        street->openDoor();
        street->moveRight();
        int n = 1;
        while(true) {
            if( street->isDoorOpen() )
                break;
            ++n;
            street->moveRight();
        }

        return n;
    }
};
