
// 3147. Taking Maximum Energy From the Mystic Dungeon
// https://leetcode.com/problems/taking-maximum-energy-from-the-mystic-dungeon/




class Solution {
public:
    int maximumEnergy(vector<int>& energy, int k) {
        int n = energy.size();

        int ans = INT_MIN;
        vector<int> mem(n);

        for(int i = n-1; i >= 0; --i) {
            int nxt = i + k;
            if( nxt >= n ) {
                ans = max(ans, energy[i]);
                mem[i] = energy[i];

            } else {
                ans = max(ans, energy[i] + mem[nxt]);
                mem[i] = energy[i] + mem[nxt];
            }
        }

        return ans;
    }
};
