
// 1282. Group the People Given the Group Size They Belong To
// https://leetcode.com/problems/group-the-people-given-the-group-size-they-belong-to/




class Solution {
public:
    vector<vector<int>> groupThePeople(vector<int>& groupSizes) {
        vector<int> b[501];

        int i,j,k=0;
        for(i = 0; i < groupSizes.size(); ++i)
            b[groupSizes[i]].push_back(i);

        vector<vector<int>> ans;
        vector<int> v;
        for(i = 1; i < 501; ++i) {
            for(j = 0; j < b[i].size(); ++j) {
                v.push_back(b[i][j]);
                ++k;
                if( k == i ) {
                    ans.push_back(v);
                    k = 0;
                    v = {};
                }
            }
        }

        return ans;
    }
};
