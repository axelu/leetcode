
// 1057. Campus Bikes
// https://leetcode.com/problems/campus-bikes/






class Solution {
private:
    int manhattan(int x1, int y1, int x2, int y2) {
        return abs(x1 - x2) + abs(y1 - y2);
    }

public:
    vector<int> assignBikes(vector<vector<int>>& workers, vector<vector<int>>& bikes) {
        int n = workers.size();
        int m = bikes.size();   // n <= m, 1 <= n <= m <= 1000

        vector<array<int,3>> v(m*n);    // distance,workedIdx,bikeIdx
        int k = 0, i = 0,j;
        for(; i < n; ++i)               // worker
            for(j = 0; j < m; ++j) {    // bike
                v[k] =  {manhattan(workers[i][0],workers[i][1],bikes[j][0],bikes[j][1]),i,j};
                ++k;
            }

       sort(begin(v),end(v),[](const array<int,3>& a, const array<int,3>& b){
            if( a[0] < b[0] ) {
                return true;
            } else if( a[0] == b[0] ) {
                if( a[1] < b[1] ) {
                    return true;
                } else if( a[1] == b[1] ) {
                    if( a[2] < b[2] ) {
                        return true;
                    }
                }
            }
            return false;
        });

        int worker[n];memset(worker,0,sizeof worker);
        int bike[m];memset(bike,0,sizeof bike);

        vector<int> ans(n);
        int c = 0; // count of assigned workers
        for(k = 0; k < m*n; ++k) {
            if( !worker[v[k][1]] && !bike[v[k][2]] ) {
                ans[v[k][1]] = v[k][2];
                worker[v[k][1]] = 1;
                bike[v[k][2]] = 1;
                ++c;
                if( c == n )
                    break;
            }
        }

        return ans;
    }
};
