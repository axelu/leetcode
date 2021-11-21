
// 174. Dungeon Game
// https://leetcode.com/problems/dungeon-game/submissions/ 
// day 2 October 2021 challenge




class Solution {
private:
    int m,n;

    // directions right,down
    int dirR[2] = {0,1};
    int dirC[2] = {1,0};

    int rec(vector<vector<int>>& dungeon, int i, int j, int mem[]) {
        // cout << "rec i " << i << " j " << j << endl;
        int ret;
        if( i == m-1 && j == n-1 ) {
            ret = dungeon[i][j] <= 0 ? 1 - dungeon[i][j] : 1;
            // cout << "rec i " << i << " j " << j << " return " << ret << endl;
            return ret;
        }

        int memIdx = i*n+j;
        if( mem[memIdx] != -1 )
            return mem[memIdx];

        int t = INT_MAX;
        int i_new,j_new;
        for(int k = 0; k < 2; ++k) {
            i_new = i + dirR[k];
            if( i_new == m )
                continue;
            j_new = j + dirC[k];
            if( j_new == n )
                continue;

            t = min(t,rec(dungeon,i_new,j_new,mem));

        }

        ret = dungeon[i][j] < t ? t - dungeon[i][j] : 1;
        // cout << "rec i " << i << " j " << j << " return " << ret << endl;

        return mem[memIdx] = ret;
    }

public:
    int calculateMinimumHP(vector<vector<int>>& dungeon) {
        m = dungeon.size();
        n = dungeon[0].size();

        int mem[m*n];memset(mem,-1,sizeof mem);
        return rec(dungeon,0,0,mem);
    }
};
