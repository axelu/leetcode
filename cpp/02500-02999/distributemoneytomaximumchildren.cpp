
// 2591. Distribute Money to Maximum Children
// https://leetcode.com/problems/distribute-money-to-maximum-children/



class Solution {
public:
    int distMoney(int money, int children) {

        // cannot meet rule that
        // everyone must receive at least 1 dollar.
        if( money < children )
            return -1;
        else if( money == children )
            return 0;

        // give everyone one dollar
        money -= children;

        // not enough money left to give at least one
        // eight dollars total
        if( money < 7 )
            return 0;

        // give 7 dollars as long as we can

        int i = 0;
        for(; i < children; ++i) {
            // give child i 7 dollars
            money -= 7;

            if( money == 0 ) {
                return i + 1;
            } else if( money < 7 ) {
                // we have a problem if
                //   one child left and 3 dollar left
                if( children - i - 1 == 1 && money == 3 )
                    return i;
                else if( i != children-1 )
                    return i + 1;
                else
                    return i;
            }
        }

        return children - 1;
    }
};
