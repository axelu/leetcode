
// 1927. Sum Game
// https://leetcode.com/problems/sum-game/



/* rephrasing the goal:
 *   can Alice prevent Bob from winning?
 *   -> can Alice prevent Bob from equalizing the sums
 *
 * edge cases that should be covered by our solution:
 *   no '?' in string, then the math will have the answer
 *   string is composed out of '?' only, Bob will always win
 *
 * Truth: we cannot make a sum smaller!
 *
 * cases:
 *   sum1                            >  sum2
 *   --------------------------------------------------------------------
 *   a: place 9s to keep sum greater    a: place 0s to keep sum smaller
 *                                      b: place 9s to make sum greater
 *   Solution:
 *   the question marks in the 1st half and second half cancel each other out
 *   after that:
 *   if there are '?' only left in the 1st half -> Alice wins
 *   if there are '?' only left in the 2nd half
 *       let x be the number of question marks in the second half
 *       Bob will be able to use x/2 of those, if x/2 * 9 >= diff, Bob wins
 *
 *   sum1                            <  sum2
 *   --------------------------------------------------------------------
 *   Note: we can always switch the halfs,
 *         so the above two cases are really only one case
 *
 *   sum1                            == sum2
 *   --------------------------------------------------------------------
 *   Alice will want to change the state, and Bob wants to keep up with
 *     Alice's moves to maintain the state
 *     if there is an equal number of '?' in both halfs, Bob wins
 *     in all other cases, Alice wins
 *
 *   examples:   90?? Bob wins
 *               1900?? Alice wins
 */
class Solution {
public:
    bool sumGame(string num) {
        // Alice wins: return true
        // Bob wins: return false

        int n = num.size();

        // 1st half
        int sum1 = 0, cnt1 = 0;
        for(int i = 0; i < n/2; ++i)
            if( num[i] == '?' )
                ++cnt1;
            else
                sum1 += (num[i] - '0');

        // 2nd half
        int sum2 = 0, cnt2 = 0;
        for(int i = n/2; i < n; ++i)
            if( num[i] == '?' )
                ++cnt2;
            else
                sum2 += (num[i] - '0');

        if( sum1 == sum2 )
            return cnt1 == cnt2 ? false : true;

        if( sum1 < sum2 ) { // swap
            int t = sum1;
            sum1 = sum2;
            sum2 = t;
            t = cnt1;
            cnt1 = cnt2;
            cnt2 = t;
        }

        // sum1 > sum2

        if( cnt1 < cnt2 ) {

            int sum_diff = sum1 - sum2;
            int cnt_diff = cnt2 - cnt1;

            if( cnt_diff % 2 == 0 && cnt_diff/2 * 9 == sum_diff )
                return false;
        }

        return true;
    }
};
