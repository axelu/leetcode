
// 3538. Merge Operations for Minimum Travel Time
// https://leetcode.com/problems/merge-operations-for-minimum-travel-time/




class Solution {
private:
    const int INF = 500000001;

    int mem[50][11][11];

    int rec(vector<int>& position, vector<int>& time, int i, int j, int s, int k) {
        int n = position.size();
        if( i == n-1 )
            return j == k ? 0 : INF;

        if( mem[i][j][s] != -1 )
            return mem[i][j][s];

        // what is the speed with which we travel starting at our position i?
        // TODO speed up uisng prefixSum
        int _time = time[i];
        for(int o = 1; o <= s; ++o)
            _time += time[i-o];

        // we have a choice
        //     don't merge OR
        //     merge

        int ret = (_time * (position[i+1] - position[i])) + rec(position, time, i+1, j, 0, k);

        int merges = 1;
        for(int o = i+2; o < n; ++o) {
            if( j + merges > k )
                break;

            ret = min(ret, (_time * (position[o] - position[i])) + rec(position, time, o, j + merges, merges, k));
            ++merges;
        }

        return mem[i][j][s] = ret;
    }

public:
    int minTravelTime(int l, int n, int k, vector<int>& position, vector<int>& time) {
        // handle n = 2
        if( n == 2 ) {
            return l * time[0];
        }

        memset(mem,-1,sizeof mem);
        return rec(position, time, 0, 0, 0, k);
    }
};
