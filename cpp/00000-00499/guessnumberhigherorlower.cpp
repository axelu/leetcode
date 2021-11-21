
// 374. Guess Number Higher or Lower
// https://leetcode.com/problems/guess-number-higher-or-lower/

/**
 * Forward declaration of guess API.
 * @param  num   your guess
 * @return 	     -1 if num is lower than the guess number
 *			      1 if num is higher than the guess number
 *               otherwise return 0
 * int guess(int num);
 */

class Solution {
public:
    int guessNumber(int n) {
        int s = 1;
        int e = n;
        int pick = s + ((e - s)/2);
        int result = guess(pick);
        while( result != 0 ) {
            if( result == -1 )
                e = pick-1;
            else
                s = pick+1;
            pick = s + ((e - s)/2);
            result = guess(pick);
        }
        return pick;
    }
};
