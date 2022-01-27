
// 860. Lemonade Change
// https://leetcode.com/problems/lemonade-change/



class Solution {
public:
    bool lemonadeChange(vector<int>& bills) {
        int change[21]; memset(change,0,sizeof change);

        for(int i = 0; i < bills.size(); ++i) {
            if( bills[i] == 5 ) {
                ++change[5];
            } else if( bills[i] == 10 ) {
                if( change[5] > 0 ) {
                    --change[5];
                    ++change[10];
                } else {
                    return false;
                }
           } else {
                // bills[i] == 20
                // preserve 5's, so we will first attemtp to use 10's
                if( change[10] > 0 && change[5] > 0 ) {
                    --change[10];
                    --change[5];
                    ++change[20];
                } else if( change[5] > 2 ) {
                    change[5] -= 3;
                    ++change[20];
                } else {
                    return false;
                }
            }
        }
        return true;

    }
};
