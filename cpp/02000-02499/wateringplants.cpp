
// 2079. Watering Plants
// https://leetcode.com/problems/watering-plants/




class Solution {
public:
    int wateringPlants(vector<int>& plants, int capacity) {
        int n = plants.size();
        // max(plants[i]) <= capacity
        if( n == 1 )
            return 1;

        // base cases to explore:
        //   - capacity equal or greater than complete water demand (sum)
        //     answer = n;
        //   - capacity equal than min of all plants
        //     answer = 2*1 + 2*2 + ... + 2*(n-1) + n
        //     worst case n = 1000 -> answer = 1000000

        // start at river with full watering can and walk to plant 0
        int ans = 1;
        int f = capacity;
        for(int i = 0; i < n-1; ++i) {
            f -= plants[i];     // water the current plant
            if( plants[i+1] > f ) {
                ans += i+1;     // return to river
                f = capacity;   // fill can
                ans += i+2;     // go from river to next plant
            } else {
                ++ans;          // go from current plant to next plant
            }
        }

        return ans;
    }
};
