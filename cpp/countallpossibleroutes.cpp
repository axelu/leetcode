
// 1575. Count All Possible Routes
// https://leetcode.com/problems/count-all-possible-routes/




class Solution {
private:
    long MOD = 1000000007;
    long mem[100][201]; // city index, fuel left

    long rec(vector<int>& locations, int n, int cityIndex, int remainingFuel, int finish) {

        if( remainingFuel == 0 )
            return 0;

        if( mem[cityIndex][remainingFuel] != -1 )
            return mem[cityIndex][remainingFuel];

        // we have a choice to go to every other city
        // as long as we have enough fuel to make it there

        long ans = 0;

        int fuel;
        for(int i = 0; i < n; ++i) { // cityIndex
            if( i == cityIndex )
                continue;

            fuel = abs(locations[cityIndex]-locations[i]);
            if( fuel <= remainingFuel ) {
                if( i == finish )
                    ++ans;
                ans = (ans + rec(locations,n,i,remainingFuel-fuel,finish)) %MOD;
            }
        }

        return mem[cityIndex][remainingFuel] = ans;
    }

public:
    int countRoutes(vector<int>& locations, int start, int finish, int fuel) {
        int n = locations.size();

        for(int i = 0; i < n; ++i)
            for(int j = 0; j <= fuel; ++j)
                mem[i][j] = -1;

        long ans = rec(locations,n,start,fuel,finish);
        return start == finish ? (ans+1) % MOD : ans;
    }
};
