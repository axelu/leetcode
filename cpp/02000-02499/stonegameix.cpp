
// 2029. Stone Game IX
// https://leetcode.com/problems/stone-game-ix/




class Solution {
private:
    bool simulate(int alice, int pile, int draw, int rem[]) {
        // alice == 1 -> alice, alice == 0 -> bob
        // pile -> rem of pile, initially 0

        // cout << draw << endl;

        // play the turn
        --rem[draw];
        int pile_new   = (pile + draw) % 3;
        int player_new = !alice;

        // is there a next move?
        // we will draw from rem 1 and 2 first
        if( pile_new == 1 ) {
            if( rem[1] > 0 ) {
                return simulate(player_new,pile_new,1,rem);
            } else if( rem[0] > 0 ) {
                return simulate(player_new,pile_new,0,rem);
            } else if( rem[2] > 0 ) {
                // next player looses
                return player_new == 0 ? true : false;
            } else {
                // we ran out of stones -> Bob wins
                return false;
            }
        } else {
            // pile_new == 2
            if( rem[2] > 0 ) {
                return simulate(player_new,pile_new,2,rem);
            } else if( rem[0] > 0 ) {
                return simulate(player_new,pile_new,0,rem);
            } else if( rem[1] > 0 ) {
                // next player looses
                return player_new == 0 ? true : false;
            } else {
                // we ran out of stones -> Bob wins
                return false;
            }
        }
    }

public:
    bool stoneGameIX(vector<int>& stones) {
        int n = stones.size(); // 1 <= stones.length <= 105
        if( n == 1 ) // Alice looses regardless of what type of stone(s)
            return false;

        // if there are no stones with remainder 1 or 2 to begin with,
        // Alice looses, as she has to start and value of the removed stone is divisible by 3

        // what move keeps the sum of the values of removed stones indivisible by 3?
        // if the current sum of the values of all removed stones
        //    has a remainder of 1, then one can pick a stone with remainder of 1 or 0 OR
        //    has a remainder of 2, then one can pick a stone with remainder of 2 or 0
        // to keep the sum of the values of all removed stones indivisible by 3
        // if we pick stone with remainder of 0, the remainder of the pile stays unchanged
        // if we pick stone with same remainder as pile, the pile's remainder will toggle
        // pile remainder 1 -> add stone w/ remainder of 1 -> pile remainder 2
        // pile remainder 2 -> add stone w/ remainder of 2 -> pile remainder 1

        // if we run out of stones, meaning both players on their turns kept
        // the sum of the values of all removed stones indivisible by 3 aka
        // play optimally, then Bob wins

        // we have the following scenarios
        // stones with
        //    rem 1      0  !0   0  !0   0  !0  !0
        //    rem 2      0   0  !0   0  !0  !0  !0
        //    rem 0     !0  !0  !0   0   0   0  !0
        //   winner      B   x   x   B   B   A   y

        int rem[3]; rem[0] = 0, rem[1] = 0 , rem[2] = 0;
        for(int i : stones )
            ++rem[i%3];

        // cout << "1s " << rem[1] << " 2s " << rem[2] << " 0s " << rem[0] << endl;

        if( rem[1] == 0 && rem[2] == 0 && rem[0] != 0 ) {
            return false;       // Bob wins
        } else if( rem[0] == 0 ) {
            if( rem[1] == 0 || rem[2] == 0 ) {
                return false;   // Bob wins
            } else {
                return true;    // Alice wins
            }
        }

        if( rem[2] == 0 ) {
            return simulate(1,0,1,rem); // Alice starts, nothing in pile, draw from 1s
        } else if( rem[1] == 0 ) {
            return simulate(1,0,2,rem); // Alice starts, nothing in pile, draw from 2s
        } else {
            // if Alice can win one, she wins
            // park initial state
            int t0 = rem[0], t1 = rem[1], t2 = rem[2];

            bool play = simulate(1,0,1,rem); // Alice starts, nothing in pile, draw from 1s
            if( play )
                return true;

            // reset
            rem[0] = t0, rem[1] = t1 , rem[2] = t2;
            return simulate(1,0,2,rem);     // Alice starts, nothing in pile, draw from 2s
        }
    }
};
