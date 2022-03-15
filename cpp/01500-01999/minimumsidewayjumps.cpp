
// 1824. Minimum Sideway Jumps
// https://leetcode.com/problems/minimum-sideway-jumps/


class Solution {
private:
public:
    int minSideJumps(vector<int>& obstacles) {
        int n = obstacles.size();
        if( n == 2 )
            return 0;

        int pre1 = 0, pre2 = 0, pre3 = 0;
        int cur1,cur2,cur3;
        for(int i = n-2; i >= 0; --i) {
            // if we are not at an obstacle, we can move right
            cur1 = obstacles[i] != 1 ? pre1 : 1000000;
            cur2 = obstacles[i] != 2 ? pre2 : 1000000;
            cur3 = obstacles[i] != 3 ? pre3 : 1000000;

            if( obstacles[i] != 1 ) // we could also jump to lane 2 or lane 3
                cur1 = min({cur1,cur2+1,cur3+1});
            if( obstacles[i] != 2 ) // we could also jump to lane 1 or lane 3
                cur2 = min({cur2,cur1+1,cur3+1});
            if( obstacles[i] != 3 ) // we could also jump to lane 1 or lane 2
                cur3 = min({cur3,cur2+1,cur1+1});

            pre1 = cur1;
            pre2 = cur2;
            pre3 = cur3;
        }

        return cur2;
    }
};
