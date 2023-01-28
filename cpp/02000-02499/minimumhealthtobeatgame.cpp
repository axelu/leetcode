
// 2214. Minimum Health to Beat Game
// https://leetcode.com/problems/minimum-health-to-beat-game/



class Solution {
public:
    long long minimumHealth(vector<int>& damage, int armor) {
        int n = damage.size();  // game levels 0 to n-1

        long sum = 0;
        int mx = 0;

        for(int k: damage) {
            sum += k;
            mx = max(mx,k);
        }

        return mx > armor ? sum - armor +1 : sum - mx +1;
    }
};
