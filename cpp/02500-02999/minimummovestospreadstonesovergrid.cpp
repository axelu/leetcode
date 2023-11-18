
// 2850. Minimum Moves to Spread Stones Over Grid
// https://leetcode.com/problems/minimum-moves-to-spread-stones-over-grid/




class Solution {
private:
    int rec(vector<int>& v0, int i, vector<pair<int,int>>& vm) {
        int v0_sz = v0.size();
        if( i == v0_sz )
            return 0;

        int idx0 = v0[i];
        int i0 = idx0 / 3;
        int j0 = idx0 % 3;

        int ret = INT_MAX;

        for(int j = 0; j < vm.size(); ++j) {
            if( vm[j].second == 1 )
                continue;

            int idxm = vm[j].first;
            int im = idxm / 3;
            int jm = idxm % 3;
            int mt = abs(i0 - im) + abs(j0 - jm); // cost
            --vm[j].second;
            ret = min(ret, mt + rec(v0,i+1,vm));
            // backtrack
            ++vm[j].second;
        }

        return ret;
    }

public:
    int minimumMoves(vector<vector<int>>& grid) {
        int n = 3; // it's a 3 x 3 grid

        vector<int> v0; // list of cells w/o stones
        vector<pair<int,int>> vm; // list of cells with more than one stone; idx,nbr stones

        for(int i = 0; i < 3; ++i) {
            for(int j = 0; j < 3; ++j) {
                int idx = i * n + j;
                if( grid[i][j] == 0 ) {
                    v0.push_back(idx);
                } else if( grid[i][j] > 1 ) {
                    vm.push_back({idx,grid[i][j]});
                }
            }
        }

        return rec(v0,0,vm);
    }
};
