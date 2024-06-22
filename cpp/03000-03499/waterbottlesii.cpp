
// 3100. Water Bottles II
// https://leetcode.com/problems/water-bottles-ii/





class Solution {
public:
    int maxBottlesDrunk(int numBottles, int numExchange) {

        int full_bottles  = numBottles;
        int empty_bottles = 0;
        int bottles_drunk = 0;

        while( full_bottles > 0 || empty_bottles >= numExchange ) {

            // we can do one of two operations
            //    drink OR
            //    exchange

            if( full_bottles > 0 ) {
                // drink
                empty_bottles += full_bottles;
                bottles_drunk += full_bottles;
                full_bottles = 0;

            } else {
                // exchange
                while( empty_bottles >= numExchange ) {
                    empty_bottles -= numExchange;
                    ++numExchange;
                    ++full_bottles;
                }
            }
        }

        return bottles_drunk;
    }
};
