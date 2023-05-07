
// 1276. Number of Burgers with No Waste of Ingredients
// https://leetcode.com/problems/number-of-burgers-with-no-waste-of-ingredients/




class Solution {
public:
    vector<int> numOfBurgers(int tomatoSlices, int cheeseSlices) {
        // Jumbo Burger: 4 tomato slices and 1 cheese slice.
        // Small Burger: 2 Tomato slices and 1 cheese slice.

        // brute force

        for(int j = tomatoSlices / 4; j >= 0; --j) { // j == number of jumbo burgers
            // if we make j Jumbo Burgers,
            // then we need to consume the remaining tomatoSlices
            // and the remaining cheeseSlices with the Small Burger

            int remaining_tomatoSlices = tomatoSlices - (j * 4);
            int remaining_cheeseSlices = cheeseSlices - j;          // number of small burgers

            if( remaining_tomatoSlices == 2 * remaining_cheeseSlices )
                return {j,remaining_cheeseSlices};
        }

        return {}; // total_jumbo, total_small
    }
};
