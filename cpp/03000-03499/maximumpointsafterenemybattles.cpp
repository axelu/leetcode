
// 3207. Maximum Points After Enemy Battles
// https://leetcode.com/problems/maximum-points-after-enemy-battles/



class Solution {
public:
    long long maximumPoints(vector<int>& enemyEnergies, int currentEnergy) {
        long long sum = 0LL;
        long long mn = INT_MAX;
        for(long long x: enemyEnergies) {
            mn = min(mn, x);
            sum += x;
        }

        if( mn > currentEnergy )
            return 0LL;

        long long ans = 1LL;
        long long llcurEnergy = currentEnergy - mn;
        llcurEnergy += sum - mn;

        ans += llcurEnergy / mn;

        return ans;
    }
};
