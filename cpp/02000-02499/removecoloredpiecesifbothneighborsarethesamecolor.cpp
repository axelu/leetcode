
// 2038. Remove Colored Pieces if Both Neighbors are the Same Color
// https://leetcode.com/problems/remove-colored-pieces-if-both-neighbors-are-the-same-color/




class Solution {
public:
    bool winnerOfGame(string colors) {
        // Alice moves first
        // number of moves Alice can make <= number of moves Bob can make: Bob wins
        // number of moves Alice can make > number of moves Bob can make: Bob wins


        int bob = 0;
        int alice = 0;

        int n = colors.size();
        char pre = '#';
        int cnt = 0;
        for(int i = 0; i < n; ++i) {

            if( colors[i] != pre ) {
                if( cnt >= 3 ) {
                    if( pre == 'A' ) {
                        alice += cnt - 2;
                    } else {
                        bob += cnt - 2;
                    }
                }
                pre = colors[i];
                cnt = 0;
            }
            ++cnt;
        }
        // finish up
        if( cnt >= 3 ) {
            if( pre == 'A' ) {
                alice += cnt - 2;
            } else {
                bob += cnt - 2;
            }
        }

        return alice > bob;
    }
};
