
// 3259. Maximum Energy Boost From Two Drinks
// https://leetcode.com/problems/maximum-energy-boost-from-two-drinks/





class Solution {
private:

    int * mem[2];

    long long rec(vector<int>& energyDrinkA, vector<int>& energyDrinkB, int n, int drink, int i, long long ** mem) {
        if( i >= n )
            return 0LL;

        if( mem[drink][i] != -1LL )
            return mem[drink][i];


        // we have a choice
        // consume the current drink and stay on our drink type OR
        // consume the current drink and switch

        long long ret = drink == 0 ? energyDrinkA[i] : energyDrinkB[i];

        long long a = ret + rec(energyDrinkA, energyDrinkB, n, drink, i+1, mem);
        long long b = ret + rec(energyDrinkA, energyDrinkB, n, !drink, i+2, mem);

        return mem[drink][i] = max(a, b);
    }

public:
    long long maxEnergyBoost(vector<int>& energyDrinkA, vector<int>& energyDrinkB) {
        int n = energyDrinkA.size(); // energyDrinkA.size() == energerDrinkB.size()

        long long **mem;
        mem = new long long *[2];
        for(int i = 0; i < 2; ++i) {
            mem[i] = new long long[n];
            for(int j = 0; j < n; ++j)
                mem[i][j] = -1LL;
        }

        long long a = rec(energyDrinkA, energyDrinkB, n, 0, 0, mem);
        long long b = rec(energyDrinkA, energyDrinkB, n, 1, 0, mem);

        return max(a, b);
    }
};
