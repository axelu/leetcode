
// 370. Range Addition
// https://leetcode.com/problems/range-addition/




class Solution {
public:
    vector<int> getModifiedArray(int length, vector<vector<int>>& updates) {
        vector<int> ans(length,0);

        // not handled integer overflow

        // pass 1
        for(int i = 0; i < updates.size(); ++i) {
            ans[updates[i][0]] += updates[i][2];
            if( updates[i][1] < length-1 ) ans[updates[i][1]+1] -= updates[i][2];
        }
        // pass 2
        int prev = 0;
        for(int i = 0; i < length; ++i) {
            ans[i] += prev;
            prev = ans[i];
        }
        return ans;
    }
};
