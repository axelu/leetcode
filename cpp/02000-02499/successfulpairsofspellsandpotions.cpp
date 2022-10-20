
// 2300. Successful Pairs of Spells and Potions
// https://leetcode.com/problems/successful-pairs-of-spells-and-potions/



class Solution {
public:
    vector<int> successfulPairs(vector<int>& spells, vector<int>& potions, long long success) {
        int n = spells.size();
        int m = potions.size();

        sort(potions.begin(),potions.end());

        vector<int> ans(n);
        for(int i = 0; i < n; ++i) {
            long long r = ceil((double)success/spells[i]);

            auto lb = lower_bound(potions.begin(),potions.end(),r);
            ans[i] = m - distance(potions.begin(),lb);
        }

        return ans;
    }
};
