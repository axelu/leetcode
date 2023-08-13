
// 2739. Total Distance Traveled
// https://leetcode.com/problems/total-distance-traveled/



class Solution {
public:
    int distanceTraveled(int mainTank, int additionalTank) {
        int ans = 0;

        while( mainTank > 0 ) {
            if( mainTank >= 5 ) {
                ans += 50;
                mainTank -= 5;
                if( additionalTank >= 1 ) {
                    mainTank += 1;
                    --additionalTank;
                }
            } else {
                ans += mainTank * 10;
                mainTank = 0;
            }
        }

        return ans;
    }
};
