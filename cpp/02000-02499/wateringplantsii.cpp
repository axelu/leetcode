
// 2105. Watering Plants II
// https://leetcode.com/problems/watering-plants-ii/



class Solution {
public:
    int minimumRefill(vector<int>& plants, int capacityA, int capacityB) {
        int n = plants.size();

        int alice_idx = 0;
        int alice_wtr = capacityA;
        int bob_idx = n-1;
        int bob_wtr = capacityB;

        int refills = 0;

        while( alice_idx <= bob_idx ) {
            if( alice_idx == bob_idx ) {
                int wtr = max(alice_wtr,bob_wtr);
                if( wtr < plants[alice_idx] )
                    ++refills;
                break;
            }

            // Alice
            if( alice_wtr >= plants[alice_idx] ) {
                alice_wtr -= plants[alice_idx];
            } else {
                ++refills;
                alice_wtr = capacityA;
                alice_wtr -= plants[alice_idx];
            }

            // Bob
            if( bob_wtr >= plants[bob_idx] ) {
                bob_wtr -= plants[bob_idx];
            } else {
                ++refills;
                bob_wtr = capacityB;
                bob_wtr -= plants[bob_idx];
            }

            ++alice_idx;
            --bob_idx;
        }

        return refills;
    }
};
