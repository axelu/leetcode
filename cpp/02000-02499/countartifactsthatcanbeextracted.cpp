
// 2201. Count Artifacts That Can Be Extracted
// https://leetcode.com/problems/count-artifacts-that-can-be-extracted/



class Solution {
public:
    int digArtifacts(int n, vector<vector<int>>& artifacts, vector<vector<int>>& dig) {
        vector<vector<bool>> grid(n,vector<bool>(n,false));

        for(auto& v: dig)
            grid[v[0]][v[1]] = true;

        int ans = 0;
        for(auto& v: artifacts) {

            bool f = true;
            for(int i = v[0]; i <= v[2]; ++i)
                for(int j = v[1]; j <= v[3]; ++j)
                    if( !grid[i][j] ) {
                        f = false;
                        break;
                    }

            ans += f;
        }

        return ans;
    }
};
