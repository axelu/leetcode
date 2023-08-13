
// 810. Chalkboard XOR Game
// https://leetcode.com/problems/chalkboard-xor-game/





/* c = a^b = b^a
 * inverse:
 * a = c^b = b^c (order is not important)
 * b = c^a = a^c
 *
 * for XOR to become 0, the number of set bits in a position has to become even
 * so a player wins, if the player can force all bits to become even
 */
class Solution {
public:
    bool xorGame(vector<int>& nums) {
        int n = nums.size();

        // returns true if Alice wins, returns false if Bob wins
        // Alice starts

        unordered_multiset<int> umst;
        int c = 0; // XOR of all elements on the board
        for(int x: nums) {
            c = c ^ x;
            umst.insert(x);
        }

        if( c == 0 )
            return true; // Alice wins

        for(int i = 0; i < n; ++i) {    // round
            // if the current player cannot find an element
            // that does not cause the current xor to become 0
            // then that player looses
            // even round => Alice's turn
            // odd round  => Bob's turn
            bool f = false;
            for(auto it = umst.begin(); it != umst.end(); ++it) {
                if( *it != c ) {
                    f = true;
                    c = c ^ *it;
                    umst.erase(it);
                    break;
                }
            }
            if( !f )
                return i % 2;
        }

        // we should never get here! because if in above loop we
        // will eventually hit the last element
        // if we are still here, then Alice will win if the number
        // of elements is even, because Bob will have to remove the
        // last element
        return n % 2 == 0;
    }
};
