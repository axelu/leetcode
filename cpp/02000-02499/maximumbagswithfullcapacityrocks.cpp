
// 2279. Maximum Bags With Full Capacity of Rocks
// https://leetcode.com/problems/maximum-bags-with-full-capacity-of-rocks/




class Solution {
public:
    int maximumBags(vector<int>& capacity, vector<int>& rocks, int additionalRocks) {
        int n = capacity.size(); // capacity.length == rocks.length
        vector<int> rem(n);
        for(int i = 0; i < n; ++i)
            rem[i] = capacity[i]-rocks[i];

        sort(rem.begin(),rem.end());

        int ans = 0;

        for(int i = 0; i < n; ++i) {
            if( rem[i] == 0 ) {
                ++ans;
                continue;
            }
            if( rem[i] <= additionalRocks ) {
                additionalRocks -= rem[i];
                ++ans;
            } else {
                break;
            }
        }

        return ans;
    }
};
